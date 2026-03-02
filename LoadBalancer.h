#ifndef LOADBALANCER_H
#define LOADBALANCER_H
#include <string>
#include <queue>
#include "WebServer.h"
#include "Request.h"
#include <vector>
#include "RequestQueue.h"
#include <string>
#include <memory>
/**
 * @brief LoadBalancer class managing the Queue and Servers
 * 
 */
class LoadBalancer {

    public:
        /**
         * @brief Vector of servers for the loadbalancer to manage
         * 
         */
        std::vector<std::unique_ptr<WebServer>> servers;
        /**
         * @brief Queue of requests for the loadbalancer to manage
         * 
         */
        RequestQueue liveQueue;
        /**
         * @brief Number of starting servers
         * 
         */
        int n;
        /**
         * @brief Index or id for the load balancer
         * 
         */
        int loadBalancerIndex;
        void setAlternative(RequestQueue &alternative);
        LoadBalancer(int n);

        LoadBalancer(int n, int loadBalancerIndex);

        void run();
};
#endif 