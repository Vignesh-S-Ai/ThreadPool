🚀 Multithreaded Thread Pool (C++)

A high-performance multithreaded thread pool implemented in C++17, demonstrating practical concurrency, synchronization, and scalability concepts used in real-world systems.

🔹 What This Project Does

Executes tasks concurrently using a fixed-size thread pool

Uses a bounded task queue to apply backpressure

Ensures thread safety using mutexes and condition variables

Measures performance accurately (no busy-waiting)

Evaluates scalability across multiple thread counts

🧱 Architecture (High Level)
Producer → Bounded Task Queue → Worker Threads → Task Completion

⚙️ Build & Run
g++ -std=c++17 src/ThreadPool.cpp src/main.cpp -pthread -O2 -o threadpool
./threadpool

📊 Performance Snapshot
Single-thread time : 92 ms
ThreadPool time   : 27 ms
Speedup           : ~3.4x

Scalability
Threads	Time (ms)
1	93
2	54
4	44
8	33
🧠 Key Concepts Demonstrated

Multithreading & concurrency

Producer–consumer pattern

Bounded queues & backpressure

Mutexes and condition variables

Accurate benchmarking

Scalability analysis

👤 Author

Vignesh S
Computer Science Undergraduate
Interests: Systems Programming, Operating Systems, High-Performance Computing

📜 License

Open-source for educational purposes
