#ifndef Request_H
#define Request_H
#include <string>
#include "Ip.h"
class Request {
    public:
        Ip ip_in;
        Ip ip_out;
        long time;
        char job;
        Request();
        std::string toString() const; 
};
#endif 