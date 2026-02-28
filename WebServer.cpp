#include "Request.h"
#include "Ip.h"
#include <iostream>
#include "helpers.h"
#include "WebServer.h"
#include <thread>
#include <chrono>
#include "constants.h"
WebServer::WebServer(std::string serverName) : serverName(serverName), busy(false) {}

bool WebServer::isFree(){
    std::lock_guard<std::mutex> lock(serverMutex);
    return !busy;
}

void WebServer::assign(Request newRequest){
    std::lock_guard<std::mutex> lock(serverMutex);
    if(!busy) {
        busy = true;
        std::thread([this, newRequest](){
            long time = newRequest.time;
            double timeInSeconds = time*constants::conversion;
            std::this_thread::sleep_for(std::chrono::duration<double>(timeInSeconds));
            std::cout <<"\033[34m" << getCurrentTimestamp()<<": "<<this->serverName << " completed task after " << time <<" cycles("<<timeInSeconds<<"s) of execution" <<std::endl;
            busy = false;
        }).detach();
    }
}

std::string WebServer::getName(){
    return serverName;
}