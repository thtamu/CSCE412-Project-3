#include <random>
#include "helpers.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <string>

/**
 * @brief Generate a random number 
 * 
 * @param min minimum(inclusive)
 * @param max maximum(inclusive)
 * @return long 
 */
long generateRandom(long min, long max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<long> dist(min, max);
    return dist(gen);
}

/**
 * @brief Generate a random octet(number between 0 and 255)
 * 
 * @return int 
 */
int generateOctet() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 255);
    return dist(gen);
}


/**
 * @brief Get the Current Timestamp as a formatted string
 * 
 * @return std::string 
 */
std::string getCurrentTimestamp() {
    using namespace std::chrono;
    auto now = system_clock::now();
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
    std::time_t now_c = system_clock::to_time_t(now);
    std::tm* tm_ptr = std::localtime(&now_c);  // local time
    std::ostringstream oss;
    oss << std::put_time(tm_ptr, "%Y-%m-%d %H:%M:%S") << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return oss.str();
}