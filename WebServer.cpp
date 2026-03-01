#include "Request.h"
#include "Ip.h"
#include <iostream>
#include "helpers.h"
#include "WebServer.h"
#include <thread>
#include <chrono>
#include "constants.h"
#include "unistd.h"
#include <cstdio>
#include "Firewall.h"
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
            Firewall firewall(constants::octet1_u, constants::octet1_l, 
                constants::octet2_u, constants::octet2_l,
                constants::octet3_u, constants::octet3_l,
                constants::octet4_u, constants::octet4_l);
            bool validIp = firewall.valid(newRequest);
            if(validIp){
                long time = newRequest.time;
                double timeInSeconds = time*constants::conversion;
                std::this_thread::sleep_for(std::chrono::duration<double>(timeInSeconds));
                if(isatty(fileno(stdout))){
                    std::cout<<"\033[34m";
                }
                std::cout <<getCurrentTimestamp()<<": "<<this->serverName << " completed task after " << time <<" cycles("<<timeInSeconds<<"s) of execution" <<std::endl;
            }
            else{
                if(isatty(fileno(stdout))){
                    std::cout<<"\033[34m";
                }
                std::cout <<getCurrentTimestamp()<<": "<<this->serverName << " rejected the request since it was blocked by the firewall" <<std::endl;
            }
            busy = false;
        }).detach();
    }
}

std::string WebServer::getName(){
    return serverName;
}