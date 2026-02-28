#include "Request.h"
#include <iostream>
#include "WebServer.h"
#include "LoadBalancer.h"
#include <thread>
#include <chrono>
#include "constants.h"
#include "helpers.h"
#include "Stopper.h"
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
    //start Stopper
    Stopper::start();
    while(!Stopper::stop()){
        // Goal: Keep queue size between 50 and 80 requests times the number of servers you have. 
        if(liveQueue.size()<servers.size()*50 && servers.size()>1){
            std::cout << "\033[31m"<<getCurrentTimestamp()<<": Remove server " <<servers.back()->getName() <<". Current server count: "<<servers.size()-1<< std::endl;
            servers.pop_back();
            std::this_thread::sleep_for(std::chrono::seconds(constants::checkWaitTime));
            continue;
        }
        else if(liveQueue.size()>servers.size()*80){
            serversAdded +=1;
            std::cout << "\033[32m"<<getCurrentTimestamp()<<": Add server " << serversAdded + n<<". Current server count: "<<servers.size()+1<< std::endl;
            servers.push_back(std::make_unique<WebServer>("Server "+std::to_string(serversAdded+n)));
            std::this_thread::sleep_for(std::chrono::seconds(constants::checkWaitTime));
            continue;
        }

        if(liveQueue.size() > 0){
            for(int i = 0; i < servers.size(); i++){
                if(servers[i]->isFree()){
                    std::cout << "\033[33m"<<getCurrentTimestamp()<<": Server " << servers[i]->getName() << " is free, assigning request" << std::endl;
                    servers[i]->assign(liveQueue.getRequest());
                    break;
                }
            }
        }
        
    }
    std::cout << "\033[31m"<<getCurrentTimestamp()<<": Stopping LoadBalancer"<< std::endl;
    std::cout << "Final Statistics: "<<std::endl;
    std::cout << "Final server count: " << servers.size() << std::endl;
    std::cout << "Final queue size: " << liveQueue.size() << std::endl;
}


