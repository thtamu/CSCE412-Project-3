#ifndef STOPPER_H
#define STOPPER_H

/**
 * @brief Clock manager for the LoadBalancer
 * 
 */
class Stopper {
    public:
        /**
         * @brief Starting timestamp
         * 
         */
        static std::chrono::steady_clock::time_point startPoint;
        /**
         * @brief Boolean indicating whether the clock has started yet
         * 
         */
        static std::atomic<bool> started;
        /**
         * @brief Starts the clock
         * 
         */
        static void start() {
            started.store(true);
            startPoint = std::chrono::steady_clock::now();
        }
        /**
         * @brief Checks if the clock has reached its expiration time
         * 
         * @return true if it did reach expiration time
         * @return false if it did not reach expiration time
         */
        static bool stop() {
            if (started.load()) {
                auto now =  std::chrono::steady_clock::now();
                auto upTime = std::chrono::duration_cast<std::chrono::seconds>(now - startPoint).count();
                if(upTime >= constants::runDuration) {
                    started.store(false);
                    return true;
                }
                else{
                    return false;
                }
            }
            else{
                return false;
            }
        }
};
#endif 