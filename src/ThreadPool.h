#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

class ThreadPool {
private:
    std::vector<std::thread> workers;   // Worker Threads
    std::queue<std::function<void()>> tasks; // Task Queue

    std::mutex queueMutex;              // Mutex
    std::condition_variable condition;  // Condition Variable
    std::atomic<bool> stop;             // Graceful Shutdown

public:
    ThreadPool(size_t threads);
    void enqueue(std::function<void()> task);
    ~ThreadPool();
};

#endif
