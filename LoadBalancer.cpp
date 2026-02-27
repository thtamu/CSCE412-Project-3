#include "Request.h"
#include <iostream>
#include "WebServer.h"
#include "LoadBalancer.h"
#include <thread>
#include <chrono>
#include "constants.h"

LoadBalancer::LoadBalancer(int n){
    this->n = n;
    for(int i = 0; i < n; i++){
        servers.push_back(std::make_unique<WebServer>("Server "+std::to_string(i+1)));
    }
    std::thread requestThread(&RequestQueue::generateRequest, &liveQueue);
    requestThread.detach();
}


void LoadBalancer::run(std::string logfile){
    int serversAdded = 0;
    while(true){
        // Goal: Keep queue size between 50 and 80 requests times the number of servers you have. 
        if(liveQueue.size()<servers.size()*50 && servers.size()>1){
            std::cout << "\033[31mRemove server " <<servers.back()->getName() << std::endl;
            servers.pop_back();
        }
        else if(liveQueue.size()>servers.size()*80){
            serversAdded +=1;
            std::cout << "\033[32mAdd server " << serversAdded + n << std::endl;
            servers.push_back(std::make_unique<WebServer>("Server "+std::to_string(serversAdded+n)));
        }

        if(liveQueue.size() > 0){
            for(int i = 0; i < servers.size(); i++){
                if(servers[i]->isFree()){
                    std::cout << "\033[33mServer " << servers[i]->getName() << " is free, assigning request" << std::endl;
                    servers[i]->assign(liveQueue.getRequest());
                    break;
                }
            }
        }
        
    }
}


