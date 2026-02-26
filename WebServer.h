#ifndef WEBSERVER_H
#define WEBSERVER_H
#include <string>
#include "Ip.h"
#include "Request.h"
#include <optional>
#include <mutex>
#include <atomic>

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
};
#endif 