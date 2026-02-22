#ifndef IP_H
#define IP_H
#include <string>
class Ip {

    public:
        int octet1;
        int octet2;
        int octet3;
        int octet4;
        Ip(int octet1, int octet2, int octet3, int octet4);

        Ip();

        bool operator==(const Ip& other) const;
        
        std::string toString() const; 
};
#endif 