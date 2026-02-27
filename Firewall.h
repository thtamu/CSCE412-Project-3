#ifndef FIREWALL_H
#define FIREWALL_H
#include "Request.h"
class Firewall {

    public:
        int octet1_u;
        int octet1_l;
        int octet2_u;
        int octet2_l;
        int octet3_u;
        int octet3_l;
        int octet4_u;
        int octet4_l;

        Firewall();
        Firewall(int octet1_u, int octet1_l, int octet2_u, int octet2_l, int octet3_u, int octet3_l, int octet4_u, int octet4_l);

        void update(int octet1_u, int octet1_l, int octet2_u, int octet2_l, int octet3_u, int octet3_l, int octet4_u, int octet4_l);

        bool valid(Request request);
};
#endif 