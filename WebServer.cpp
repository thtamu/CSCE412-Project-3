#include "Request.h"
#include "Ip.h"
#include <iostream>
#include "helpers.h"
#include "WebServer.h"
#include <thread>
#include <chrono>

WebServer::WebServer(){
    busy = false;
}
bool WebServer::isBusy(){
    return busy;
}
bool WebServer::isFree(){
    return !busy;
}
void WebServer::assign(Request newRequest){
    busy = true;
    request = newRequest;
}
void WebServer::process(){
    std::cout << "Start" <<std::endl;
    int time = this->request->time;
    std::cout << "Waiting "<<(time) <<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(time)); 
    busy = false;
    std::cout <<"done"<<std::endl;
}