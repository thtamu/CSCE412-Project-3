#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>

namespace constants {
    //Edit these
    inline constexpr double ghz = 2.69;
    inline constexpr long startingServers = 20;
    inline constexpr long requestIntervalLowCycles = 3e10;
    inline constexpr long requestIntervalHighCycles = 15e10;
    inline constexpr long timeLowCycles = 3e10;
    inline constexpr long timeHighCycles = 6e10;
    inline constexpr const char* logFile = "logfile.txt";
    //Don't edit these
    inline constexpr double conversion = 1/(ghz*1e9); 
    inline constexpr int requestIntervalLow = (int)(requestIntervalLowCycles*conversion);
    inline constexpr int requestIntervalHigh = (int)(requestIntervalHighCycles*conversion);
    inline constexpr int timeLow = (int)(timeLowCycles*conversion);
    inline constexpr int timeHigh = (int)(timeHighCycles*conversion);
    inline constexpr long checkWaitTime = (int)(startingServers*conversion);
}

#endif