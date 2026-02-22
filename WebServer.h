#ifndef WEBSERVER_H
#define WEBSERVER_H
#include <string>
#include "Ip.h"
#include "Request.h"
#include <optional>
class WebServer {
    private:
        std::optional<Request> request;
        bool busy;
    public:
        WebServer();
        bool isBusy();
        bool isFree();
        void assign(Request newRequest);
        void process();
};
#endif 