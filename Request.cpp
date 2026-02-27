#include "Request.h"
#include "Ip.h"
#include <iostream>
#include "helpers.h"
#include "constants.h"

Request::Request(char job){
    this->ip_in = Ip();
    this->ip_out = Ip();
    this->time = generateRandom(constants::timeLow, constants::timeHigh);
    this->job = job;
}

std::string Request::toString() const{
    return this->ip_in.toString()+"->"+this->ip_out.toString()+ " at "+std::to_string(this->time) +" Job: "+this->job;
}