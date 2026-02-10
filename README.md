# 🚀 Multithreaded Thread Pool (C++)

A high-performance multithreaded thread pool implemented in C++17, showcasing real-world concurrency, synchronization, and scalability techniques used in systems software.

---

## 🔹 Overview

This project implements a fixed-size thread pool that executes tasks concurrently while ensuring:

- Thread safety  
- Efficient synchronization  
- Controlled resource usage via bounded queues (backpressure)  
- Accurate performance measurement  
- Clean scalability analysis  

---

## 🧱 High-Level Architecture

Producer  
  ↓  
Bounded Task Queue  
  ↓  
Worker Threads (std::thread)  
  ↓  
Task Completion Notification  

---

## ⚙️ Build & Run

g++ -std=c++17 src/ThreadPool.cpp src/main.cpp -pthread -O2 -o threadpool  
./threadpool  

---

## 📊 Performance Snapshot

Single-thread time : 92 ms  
ThreadPool time   : 27 ms  
Speedup           : ~3.4x  

### Scalability

Threads | Execution Time (ms)  
1       | 93  
2       | 54  
4       | 44  
8       | 33  

---

## 🧠 Concepts Demonstrated

- Multithreading and concurrency  
- Producer–consumer pattern  
- Bounded queues and backpressure  
- Mutexes and condition variables  
- Accurate benchmarking  
- Scalability analysis  

---

## 👤 Author

Vignesh S  
Computer Science Undergraduate  

Interests:  
Systems Programming, Operating Systems, High-Performance Computing  

---

## 📜 License

Open-source for educational and learning purposes.
