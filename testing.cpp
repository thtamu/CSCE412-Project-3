#include "Ip.h"
#include "Request.h"
#include <iostream>
#include <string>
#include "WebServer.h"
#include <vector>
#include <memory>
#include "LoadBalancer.h"
#include <thread>
#include "constants.h"

/**
 * @brief Run the number of Load Balancers specified in the constants file
 * 
 * @return int 
 */
int main() {
    int n;
    std::cerr << "Enter the number of starting servers: ";
    std::cin >> n;
    if(constants::loadbalancers==2){
        LoadBalancer loadBalancer1(n, 1);
        LoadBalancer loadBalancer2(n, 2);
        loadBalancer1.setAlternative(loadBalancer2.liveQueue);
        loadBalancer2.setAlternative(loadBalancer1.liveQueue);
        std::thread loadBalancerThread1(&LoadBalancer::run, &loadBalancer1);
        std::thread loadBalancerThread2(&LoadBalancer::run, &loadBalancer2);
        loadBalancerThread1.join();
        loadBalancerThread2.join();
    }
    else{
        LoadBalancer loadBalancer1(n, 1);
        std::thread loadBalancerThread1(&LoadBalancer::run, &loadBalancer1);
        loadBalancerThread1.join();
    }
    
    return 0;
}