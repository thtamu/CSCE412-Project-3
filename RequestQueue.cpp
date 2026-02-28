#include "RequestQueue.h"
#include "Request.h"
#include <iostream>
#include <thread>
#include <memory>
#include "helpers.h"
#include "constants.h"
#include "Stopper.h"

RequestQueue::RequestQueue() {
    for(int i = 0; i < 250; i++){
        Request request('s');
        requestQueue.push(request);
    }
}
void RequestQueue::generateRequest(){
    while(!Stopper::stop()){
        std::unique_lock<std::mutex> lock(queueMutex);
        Request request('s');
        requestQueue.push(request);
        cv.notify_all();
        lock.unlock();
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