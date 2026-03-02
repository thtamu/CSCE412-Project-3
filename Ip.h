#ifndef IP_H
#define IP_H
#include <string>
/**
 * @brief Class to store information about an IP
 * 
 */
class Ip {

    public:
        /**
         * @brief Octet 1 value(0-255)
         * 
         */
        int octet1;
        /**
         * @brief Octet 2 value(0-255)
         * 
         */
        int octet2;
        /**
         * @brief Octet 3 value(0-255)
         * 
         */
        int octet3;
        /**
         * @brief Octet 4 value(0-255)
         * 
         */
        int octet4;
        Ip(int octet1, int octet2, int octet3, int octet4);

        Ip();

        bool operator==(const Ip& other) const;
        
        std::string toString() const; 
};
#endif 