# Multithreaded Thread Pool (C++)

A lightweight and efficient **multithreaded thread pool** implementation in **C++**, built using
**mutexes, condition variables, and atomic operations**.  
This project demonstrates core **operating systems and concurrency concepts**
used in high-performance systems.

---

## Overview

Thread pools are a fundamental building block in modern software systems such as
web servers, databases, and runtime engines.

This project implements a **fixed-size thread pool** that executes submitted tasks
concurrently while ensuring **thread safety**, **efficient scheduling**, and
**graceful shutdown**.

---

## Architecture

ThreadPool
├── Worker Threads (std::thread)
├── Task Queue (std::queue<std::function<void()>>)
├── Mutex (std::mutex)
├── Condition Variable (std::condition_variable)
└── Graceful Shutdown (std::atomic<bool>)


---

## Key Components

### Worker Threads
A fixed number of threads that continuously fetch and execute tasks from the shared queue.

### Task Queue
Stores pending jobs submitted to the thread pool.

### Mutex & Condition Variable
Synchronize access to the task queue and prevent busy waiting.

### Graceful Shutdown Mechanism
Ensures all worker threads exit cleanly when the thread pool is destroyed.

---

## Design Decisions

- Used **condition variables** instead of busy waiting to reduce CPU usage
- Protected shared state using **mutex locks** to ensure thread safety
- Employed an **atomic flag** to signal shutdown across all worker threads
- Followed the **producer–consumer model** for task submission and execution

---

## Build & Run

### Requirements
- C++17 compatible compiler
- POSIX thread support

### Compile
```bash
g++ -std=c++17 src/ThreadPool.cpp src/main.cpp -pthread -O2 -o threadpool
Run
./threadpool
Example Output
Task 0 executed by thread 2
Task 4 executed by thread 2
Task 2 executed by thread 3
Task 3 executed by thread 4
Task 1 executed by thread 5
Output order may vary due to concurrent execution by multiple threads.

Concepts Demonstrated
Multithreading and concurrency

Mutexes and condition variables

Producer–consumer pattern

Thread lifecycle management

Memory safety and synchronization

Graceful shutdown in concurrent systems

Possible Enhancements
Bounded task queue with backpressure

Task priority scheduling

Work-stealing between threads

Performance benchmarking and latency metrics

Thread affinity and CPU pinning

Author
Vignesh S
Computer Science Undergraduate
Interests: Systems Programming, Operating Systems, High-Performance Computing

License
This project is open-source and available for educational and learning purposes.
