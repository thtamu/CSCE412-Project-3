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

/**
 * @brief Construct a new Request Queue
 * 
 * @param index 
 */
RequestQueue::RequestQueue(int index) {
    this->index = index;
    if(constants::preloadRequests){
        for(int i = 0; i < 250; i++){
            Request request;
            requestQueue.push(request);
        }
    }
}

/**
 * @brief Push a request to the request queue
 * 
 * @param request New request
 */
void RequestQueue::push(Request request){
    std::unique_lock<std::mutex> lock(queueMutex);
    requestQueue.push(request);
    cv.notify_all();
    lock.unlock();
}

/**
 * @brief Looping algorithm that pushes new request to the queue
 * 
 */
void RequestQueue::generateRequest(){
    while(!Stopper::stop()){
        Request request;
        if(alternative==nullptr){
            push(request);
        }
        else{
            bool myJob = (request.job =='S' && index%2==0) || (request.job =='P' && index%2==1);
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

/**
 * @brief Get the new request from the queue
 * 
 * @return Request 
 */
Request RequestQueue::getRequest(){
    std::unique_lock<std::mutex> lock(queueMutex);
    cv.wait(lock, [this]{ return requestQueue.size()>0; });
    Request output = requestQueue.front();
    requestQueue.pop();
    return output;
}

/**
 * @brief Get the current size of the queue
 * 
 * @return int 
 */
int RequestQueue::size(){
    std::lock_guard<std::mutex> lock(queueMutex);
    return requestQueue.size();
}