#ifndef STOPPER_H
#define STOPPER_H

class Stopper {
    public:
        static std::chrono::steady_clock::time_point startPoint;
        static std::atomic<bool> started;
        static void start() {
            started.store(true);
            startPoint = std::chrono::steady_clock::now();
        }
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