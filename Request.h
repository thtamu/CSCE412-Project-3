#ifndef Request_H
#define Request_H
#include <string>
#include "Ip.h"
/**
 * @brief Request class, containing all information about the request
 * 
 */
class Request {
    public:
        /**
         * @brief IP address going in
         * 
         */
        Ip ip_in;
        /**
         * @brief IP address going out
         * 
         */
        Ip ip_out;
        /**
         * @brief Time for completion
         * 
         */
        long time;
        /**
         * @brief Type of job (P (processing), S (streaming))
         * 
         */
        char job;
        Request();
        std::string toString() const; 
};
#endif 