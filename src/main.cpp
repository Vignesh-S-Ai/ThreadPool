#include "ThreadPool.h"
#include <iostream>
#include <mutex>

std::mutex printMutex;

int main() {
    ThreadPool pool(4);

    for (int i = 0; i < 8; ++i) {
        pool.enqueue([i]() {
            std::lock_guard<std::mutex> lock(printMutex);
            std::cout << "Task " << i
                      << " executed by thread "
                      << std::this_thread::get_id()
                      << std::endl;
        });
    }
    return 0;
}
