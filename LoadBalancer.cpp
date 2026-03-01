#include "Request.h"
#include <iostream>
#include "WebServer.h"
#include "LoadBalancer.h"
#include <thread>
#include <chrono>
#include "constants.h"
#include "helpers.h"
#include "Stopper.h"
#include "unistd.h"
#include <cstdio>
using namespace std::chrono;
LoadBalancer::LoadBalancer(int n){
    this->n = n;
    this->loadBalancerIndex = 1;
    for(int i = 0; i < n; i++){
        servers.push_back(std::make_unique<WebServer>("Server "+std::to_string(i+1)+ "(LB"+std::to_string(loadBalancerIndex)+")"));
    }
    std::thread requestThread(&RequestQueue::generateRequest, &liveQueue);
    requestThread.detach();
}

LoadBalancer::LoadBalancer(int n, int loadBalancerIndex){
    this->n = n;
    this->loadBalancerIndex = loadBalancerIndex;
    this->loadBalancerIndex = 1;
    for(int i = 0; i < n; i++){
        servers.push_back(std::make_unique<WebServer>("Server "+std::to_string(i+1)+ "(LB"+std::to_string(loadBalancerIndex)+")"));
    }
    std::thread requestThread(&RequestQueue::generateRequest, &liveQueue);
    requestThread.detach();
}



void LoadBalancer::run(){
    int serversAdded = 0;
    //start Stopper
    Stopper::start();
    auto checkTime = steady_clock::now();
    while(!Stopper::stop()){
        auto currentTime = steady_clock::now();
        bool adjustServers = currentTime > checkTime;
        // Goal: Keep queue size between 50 and 80 requests times the number of servers you have. 
        if(liveQueue.size()<servers.size()*50 && servers.size()>1 && adjustServers){
            if(isatty(fileno(stdout))){
                std::cout<<"\033[31mLoad Balancer "<<loadBalancerIndex <<" at " << getCurrentTimestamp()<<": Remove server " <<servers.back()->getName() <<". Current server count: "<<servers.size()-1<< std::endl;
            }
            else{
                std::cout <<"Load Balancer "<< loadBalancerIndex <<" at " <<getCurrentTimestamp()<<": Remove server " <<servers.back()->getName() <<". Current server count: "<<servers.size()-1<< std::endl;
            }
            servers.pop_back();
            int waitTime = (int)(n*constants::conversion);
            checkTime = steady_clock::now() + seconds(waitTime);
            continue;
        }
        else if(liveQueue.size()>servers.size()*80 && adjustServers){
            serversAdded +=1;
            if(isatty(fileno(stdout))){
                std::cout<<"\033[32mLoad Balancer " << loadBalancerIndex <<" at " << getCurrentTimestamp()<<": Add server " << serversAdded + n<<". Current server count: "<<servers.size()+1<< std::endl;
            }
            else{
                std::cout << "Load Balancer "<<loadBalancerIndex <<" at " << getCurrentTimestamp()<<": Add server " << serversAdded + n<<". Current server count: "<<servers.size()+1<< std::endl;
            }
            servers.push_back(std::make_unique<WebServer>("Server "+std::to_string(serversAdded+n)+"(LB"+std::to_string(loadBalancerIndex)+")"));
            int waitTime = (int)(n*constants::conversion);
            checkTime = steady_clock::now() + seconds(waitTime);
            continue;
        }

        if(liveQueue.size() > 0){
            for(int i = 0; i < servers.size(); i++){
                if(servers[i]->isFree()){
                    if(isatty(fileno(stdout))){
                        std::cout<<"\033[33mLoad Balancer "<< loadBalancerIndex <<" at " << getCurrentTimestamp()<<": Server " << servers[i]->getName() << " is free, assigning request" << std::endl;
                    }
                    else{
                        std::cout <<"Load Balancer "<<loadBalancerIndex <<" at " << getCurrentTimestamp()<<": Server " << servers[i]->getName() << " is free, assigning request" << std::endl;
                    }
                    servers[i]->assign(liveQueue.getRequest());
                    break;
                }
            }
        }
        
    }
    if(isatty(fileno(stdout))){
        std::cout << "\033[0m" << getCurrentTimestamp()<<": Stopping LoadBalancer "<< loadBalancerIndex<< std::endl;
        std::cout << "\033[0m" << "Final Statistics for Load Balancer "<<loadBalancerIndex<<": "<<std::endl;
        std::cout << "\033[0m" << "Load Balancer "<<loadBalancerIndex<<" final server count: " << servers.size() << std::endl;
        std::cout << "\033[0m" << "Load Balancer "<<loadBalancerIndex<< " final queue size: " << liveQueue.size() << std::endl;
    }
    else{
        std::cout << getCurrentTimestamp()<<": Stopping LoadBalancer "<< loadBalancerIndex<< std::endl;
        std::cout << "Final Statistics for Load Balancer "<<loadBalancerIndex<<": "<<std::endl;
        std::cout << "Load Balancer "<<loadBalancerIndex<<" final server count: " << servers.size() << std::endl;
        std::cout << "Load Balancer "<<loadBalancerIndex<< " final queue size: " << liveQueue.size() << std::endl;
    }
}


