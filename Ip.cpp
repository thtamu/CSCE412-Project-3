#include "Ip.h"
#include <iostream>
#include "helpers.h"

Ip::Ip(int octet1, int octet2, int octet3, int octet4){
    this->octet1 = octet1;
    this->octet2 = octet2;
    this->octet3 = octet3;
    this->octet4 = octet4;
}

Ip::Ip(){
    this->octet1 = generateOctet();
    this->octet2 = generateOctet();
    this->octet3 = generateOctet();
    this->octet4 = generateOctet();
}

bool Ip::operator==(const Ip& other) const {
    return this->octet1==other.octet1 && this->octet2==other.octet2 && this->octet3==other.octet3 && this->octet4==other.octet4;
}

std::string Ip::toString() const{
    return std::to_string(octet1)+"."+std::to_string(octet2)+"."+std::to_string(octet3)+"."+std::to_string(octet4);
}