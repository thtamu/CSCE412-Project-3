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
class LoadBalancer {

    public:
        std::vector<std::unique_ptr<WebServer>> servers;
        RequestQueue liveQueue;
        int n;
        int loadBalancerIndex;

        LoadBalancer(int n);

        LoadBalancer(int n, int loadBalancerIndex);

        void run();
};
#endif 