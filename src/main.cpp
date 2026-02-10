#include "ThreadPool.h"
#include <iostream>
#include <chrono>
#include <atomic>
#include <thread>
#include <vector>
#include <condition_variable>
#include <mutex>

// Toggle for demo vs real benchmark
constexpr bool DEMO_MODE = true;

// CPU-bound task
void heavyTask() {
    volatile long long sum = 0;
    long long limit = DEMO_MODE ? 20000000 : 100000000;

    for (long long i = 0; i < limit; ++i) {
        sum += i;
    }
}

void printSection(const std::string& title) {
    std::cout << "\n=== " << title << " ===\n";
}

long long runBenchmark(int threadCount, int taskCount) {
    ThreadPool pool(threadCount);
    std::atomic<int> completed{0};

    std::mutex doneMutex;
    std::condition_variable doneCV;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < taskCount; ++i) {
        pool.enqueue([&]() {
            heavyTask();
            {
                std::lock_guard<std::mutex> lock(doneMutex);
                completed++;
            }
            doneCV.notify_one();
        });
    }

    std::unique_lock<std::mutex> lock(doneMutex);
    doneCV.wait(lock, [&]() {
        return completed.load() >= taskCount;
    });

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

int main() {
    const int TASK_COUNT = 8;

    std::cout << "=== ThreadPool System Demonstration ===\n";

    // 1️⃣ Thread pool info
    printSection("Thread Pool Initialization");
    std::cout << "Worker threads : configurable\n";
    std::cout << "Queue mode     : Bounded (default size = 16)\n";

    // 2️⃣ Backpressure demo
    printSection("Backpressure Demonstration");
    {
        ThreadPool pool(2, 2); // small queue to force backpressure
        for (int i = 0; i < 6; ++i) {
            pool.enqueue([]() {
                heavyTask();
            });
        }
    }

    // 3️⃣ Accurate benchmark
    printSection("Accurate Benchmark (CPU-bound workload)");

    auto singleStart = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < TASK_COUNT; ++i) {
        heavyTask();
    }
    auto singleEnd = std::chrono::high_resolution_clock::now();
    auto singleTime =
        std::chrono::duration_cast<std::chrono::milliseconds>(singleEnd - singleStart).count();

    long long poolTime = runBenchmark(4, TASK_COUNT);

    std::cout << "Single-thread time : " << singleTime << " ms\n";
    std::cout << "ThreadPool time   : " << poolTime << " ms\n";
    std::cout << "Speedup           : ~"
              << (double)singleTime / poolTime << "x\n";

    // 4️⃣ Scalability analysis
    printSection("Scalability Analysis");

    std::vector<int> threadCounts = {1, 2, 4, 8};
    for (int threads : threadCounts) {
        long long time = runBenchmark(threads, TASK_COUNT);
        std::cout << "Threads: " << threads
                  << " | Time: " << time << " ms\n";
    }

    return 0;
}
