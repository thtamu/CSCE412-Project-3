#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>

namespace constants {
    //Edit these
    inline constexpr double ghz = 1e-9;
    inline constexpr bool preloadRequests = true;
    inline constexpr int loadbalancers = 1;
    inline constexpr long requestIntervalLowCycles = 2;
    inline constexpr long requestIntervalHighCycles = 4;
    inline constexpr long timeLowCycles = 3;
    inline constexpr long timeHighCycles = 6;
    inline constexpr long runCycles = 10000;
    inline constexpr int octet1_u = 240;
    inline constexpr int octet1_l = 15;
    inline constexpr int octet2_u = 240;
    inline constexpr int octet2_l = 15;
    inline constexpr int octet3_u = 240;
    inline constexpr int octet3_l = 15;
    inline constexpr int octet4_u = 240;
    inline constexpr int octet4_l = 15;
    //Don't edit these
    inline constexpr double conversion = 1/(ghz*1e9); 
    inline constexpr int requestIntervalLow = (int)(requestIntervalLowCycles*conversion);
    inline constexpr int requestIntervalHigh = (int)(requestIntervalHighCycles*conversion);
    inline constexpr int timeLow = (int)(timeLowCycles*conversion);
    inline constexpr int timeHigh = (int)(timeHighCycles*conversion);
    inline constexpr int runDuration = (int)(runCycles*conversion);
}

#endif