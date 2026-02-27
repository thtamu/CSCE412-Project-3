#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>

namespace constants {
    inline constexpr int startingServers = 2;
    inline constexpr int requestIntervalLow = 100;
    inline constexpr int requestIntervalHigh = 500;
    inline constexpr int timeLow = 10;
    inline constexpr int timeHigh = 20;
    inline constexpr const char* logFile = "logfile.txt";
}

#endif