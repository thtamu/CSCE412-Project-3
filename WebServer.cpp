#include "Request.h"
#include "Ip.h"
#include <iostream>
#include "helpers.h"
#include "WebServer.h"
#include <thread>
#include <chrono>

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
            int time = newRequest.time;
            std::this_thread::sleep_for(std::chrono::seconds(time)); 
            std::cout <<"\033[34m" << this->serverName << " completed task after " << time <<" seconds of execution" <<std::endl;
            busy = false;
        }).detach();
    }
}

std::string WebServer::getName(){
    return serverName;
}