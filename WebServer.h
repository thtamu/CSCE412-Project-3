#ifndef WEBSERVER_H
#define WEBSERVER_H
#include <string>
#include "Ip.h"
#include "Request.h"
#include <optional>
#include <mutex>
#include <atomic>

/**
 * @brief WebServer class, managing requests assigned to it by the load balancer
 * 
 */
class WebServer {
    private:
        std::atomic<bool> busy;
        std::mutex serverMutex;
        std::string serverName;
    public:
        WebServer(std::string serverName);
        WebServer(const WebServer&) = delete;
        WebServer& operator=(const WebServer&) = delete;
        bool isFree();
        void assign(Request newRequest);
        std::string getName();
        /**
         * @brief Number of rejected requests
         * 
         */
        int rejected = 0;
        /**
         * @brief Number of accepted requests
         * 
         */
        int accepted = 0;
        /**
         * @brief Number of completed
         * 
         */
        int completed = 0;
};
#endif 