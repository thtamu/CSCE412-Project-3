#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H
#include <condition_variable>
#include <mutex>
#include "Request.h"
#include <queue>
#include <atomic>
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
        RequestQueue* alternative=nullptr;
        int index;
};
#endif 