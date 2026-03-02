#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H
#include <condition_variable>
#include <mutex>
#include "Request.h"
#include <queue>
#include <atomic>
/**
 * @brief Queue of requests for a given LoadBalancer
 * 
 */
class RequestQueue {
    private:
        std::queue<Request> requestQueue;
        std::mutex queueMutex;
        std::condition_variable cv;
        std::atomic<int> queueSize{0};
    public:
        RequestQueue(int index);
        void generateRequest();
        Request getRequest();
        int size();
        void push(Request request);
        /**
         * @brief Alternative Request Queue to push requests to
         * 
         */
        RequestQueue* alternative=nullptr;
        /**
         * @brief Index or ID for the request queue
         * 
         */
        int index;
};
#endif 