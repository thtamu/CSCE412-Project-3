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
/**
 * @brief Construct a new Web Server
 * 
 * @param serverName 
 */
WebServer::WebServer(std::string serverName) : serverName(serverName), busy(false) {}

/**
 * @brief Check if a server is free
 * 
 * @return true if it is free
 * @return false if it is busy
 */
bool WebServer::isFree(){
    std::lock_guard<std::mutex> lock(serverMutex);
    return !busy;
}

/**
 * @brief Assigns a new request to the server
 * 
 * @param newRequest Request to work on
 */
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
                accepted += 1;
                long time = newRequest.time;
                double timeInSeconds = time*constants::conversion;
                std::this_thread::sleep_for(std::chrono::duration<double>(timeInSeconds));
                std::string job = newRequest.job=='S' ? "streaming" : "processing";
                if(isatty(fileno(stdout))){
                    std::cout<<"\033[34m" <<getCurrentTimestamp()<<": "<<this->serverName << " completed " << job << " task after " << time <<" cycles("<<timeInSeconds<<"s) of execution" <<std::endl;
                }
                else{
                    std::cout <<getCurrentTimestamp()<<": "<<this->serverName << " completed " << job << " task after " << time <<" cycles("<<timeInSeconds<<"s) of execution" <<std::endl;
                }
                completed+=1;
            }
            else{
                rejected +=1;
                if(isatty(fileno(stdout))){
                    std::cout<<"\033[34m" << getCurrentTimestamp()<<": "<<this->serverName << " rejected the request since it was blocked by the firewall" <<std::endl;
                }
                else{
                    std::cout <<getCurrentTimestamp()<<": "<<this->serverName << " rejected the request since it was blocked by the firewall" <<std::endl;
                }
            }
            busy = false;
        }).detach();
    }
}

/**
 * @brief Get the name of the server
 * 
 * @return std::string 
 */
std::string WebServer::getName(){
    return serverName;
}