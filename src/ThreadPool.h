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
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queueMutex;
    std::condition_variable notEmpty;
    std::condition_variable notFull;

    std::atomic<bool> stop;
    size_t maxQueueSize;

public:
    ThreadPool(size_t threads, size_t maxQueueSize = 16);
    void enqueue(std::function<void()> task);
    ~ThreadPool();
};

#endif
