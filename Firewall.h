#ifndef FIREWALL_H
#define FIREWALL_H
#include "Request.h"
/**
 * @brief Firewall checking if requests are safe based on their IP
 * 
 */
class Firewall {

    public:
        /**
         * @brief Upper bound for octet 1
         * 
         */
        int octet1_u;
        /**
         * @brief Lower bound for octet 1
         * 
         */
        int octet1_l;
        /**
         * @brief Upper bound for octet 2
         * 
         */
        int octet2_u;
        /**
         * @brief Lower bound for octet 2
         * 
         */
        int octet2_l;
        /**
         * @brief Upper bound for octet 3
         * 
         */
        int octet3_u;
        /**
         * @brief Lower bound for octet 3
         * 
         */
        int octet3_l;
        /**
         * @brief Upper bound for octet 4
         * 
         */
        int octet4_u;
        /**
         * @brief Lower bound for octet 4
         * 
         */
        int octet4_l;

        Firewall();
        Firewall(int octet1_u, int octet1_l, int octet2_u, int octet2_l, int octet3_u, int octet3_l, int octet4_u, int octet4_l);

        void update(int octet1_u, int octet1_l, int octet2_u, int octet2_l, int octet3_u, int octet3_l, int octet4_u, int octet4_l);

        bool valid(Request request);
};
#endif 