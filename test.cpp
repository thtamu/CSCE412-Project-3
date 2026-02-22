#include "Ip.h"
#include "Request.h"
#include <iostream>
#include <string>
#include "WebServer.h"
int main() {

    std::cout << "yo"<<std::endl;
    Request r('s');
    std::cout << r.toString() << std::endl;
    WebServer ws;
    ws.assign(r);
    ws.process();
    return 0;
}