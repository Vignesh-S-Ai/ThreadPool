#include "ThreadPool.h"
#include <iostream>

ThreadPool::ThreadPool(size_t threads, size_t maxSize)
    : stop(false), maxQueueSize(maxSize) {

    for (size_t i = 0; i < threads; ++i) {
        workers.emplace_back([this]() {
            while (true) {
                std::function<void()> task;

                {
                    std::unique_lock<std::mutex> lock(queueMutex);

                    notEmpty.wait(lock, [this]() {
                        return stop || !tasks.empty();
                    });

                    if (stop && tasks.empty())
                        return;

                    task = std::move(tasks.front());
                    tasks.pop();

                    notFull.notify_one();
                }

                task();
            }
        });
    }
}

void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(queueMutex);

        // ---- Backpressure demo (prints once per full condition) ----
        if (tasks.size() >= maxQueueSize) {
            static bool printed = false;
            if (!printed) {
                std::cout << "[Backpressure] Queue full, producer waiting...\n";
                printed = true;
            }
        }

        notFull.wait(lock, [this]() {
            return stop || tasks.size() < maxQueueSize;
        });

        if (stop)
            return;

        tasks.push(std::move(task));
    }

    notEmpty.notify_one();
}

ThreadPool::~ThreadPool() {
    stop = true;
    notEmpty.notify_all();
    notFull.notify_all();

    for (std::thread &worker : workers)
        worker.join();
}
