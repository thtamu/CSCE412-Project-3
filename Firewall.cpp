#include "Firewall.h"
#include "Request.h"

Firewall::Firewall() : octet1_u(255), octet1_l(0), octet2_u(255), octet2_l(0), octet3_u(255), octet3_l(0), octet4_u(255), octet4_l(0) {}

Firewall::Firewall(int octet1_u, int octet1_l, int octet2_u, int octet2_l, int octet3_u, int octet3_l, int octet4_u, int octet4_l){
    this->octet1_u = octet1_u;
    this->octet1_l = octet1_l;
    this->octet2_u = octet2_u;
    this->octet2_l = octet2_l;
    this->octet3_u = octet3_u;
    this->octet3_l = octet3_l;
    this->octet4_u = octet4_u;
    this->octet4_l = octet4_l;
}

void Firewall::update(int octet1_u, int octet1_l, int octet2_u, int octet2_l, int octet3_u, int octet3_l, int octet4_u, int octet4_l){
    this->octet1_u = octet1_u;
    this->octet1_l = octet1_l;
    this->octet2_u = octet2_u;
    this->octet2_l = octet2_l;
    this->octet3_u = octet3_u;
    this->octet3_l = octet3_l;
    this->octet4_u = octet4_u;
    this->octet4_l = octet4_l;
}

bool Firewall::valid(Request request){
    int octet1 = request.ip_in.octet1;
    int octet2 = request.ip_in.octet2;
    int octet3 = request.ip_in.octet3;
    int octet4 = request.ip_in.octet4;
    bool octet1_valid = octet1 >= octet1_l && octet1 <= octet1_u;
    bool octet2_valid = octet2 >= octet2_l && octet2 <= octet2_u;
    bool octet3_valid = octet3 >= octet3_l && octet3 <= octet3_u;
    bool octet4_valid = octet4 >= octet4_l && octet4 <= octet4_u;
    return octet1_valid && octet2_valid && octet3_valid && octet4_valid;
}