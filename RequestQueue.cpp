#include "RequestQueue.h"
#include "Request.h"
#include <iostream>
#include <thread>
#include <memory>
#include "helpers.h"
#include "constants.h"
#include "Stopper.h"
#include "helpers.h"
#include "unistd.h"
#include <cstdio>

RequestQueue::RequestQueue(int index) {
    this->index = index;
    if(constants::preloadRequests){
        for(int i = 0; i < 250; i++){
            Request request;
            requestQueue.push(request);
        }
    }
}

void RequestQueue::push(Request request){
    std::unique_lock<std::mutex> lock(queueMutex);
    requestQueue.push(request);
    cv.notify_all();
    lock.unlock();
}

void RequestQueue::generateRequest(){
    while(!Stopper::stop()){
        Request request;
        if(alternative==nullptr){
            push(request);
        }
        else{
            bool myJob = (request.job =='s' && index%2==0) || (request.job =='p' && index%2==1);
            if(!myJob){
                alternative->push(request);
            }
            else{
                push(request);
            }

        }
        std::this_thread::sleep_for(std::chrono::milliseconds(generateRandom(constants::requestIntervalLow, constants::requestIntervalHigh)));
    }
}

Request RequestQueue::getRequest(){
    std::unique_lock<std::mutex> lock(queueMutex);
    cv.wait(lock, [this]{ return requestQueue.size()>0; });
    Request output = requestQueue.front();
    requestQueue.pop();
    return output;
}

int RequestQueue::size(){
    std::lock_guard<std::mutex> lock(queueMutex);
    return requestQueue.size();
}