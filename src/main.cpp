#include <iostream>
#include "elementQueue.h"
#include <thread>
#include <cassert>

int main() {
    Queue<int> q(2);
    q.elementPush(1);
    q.printQueue();
    
    q.elementPop();
    q.printQueue();
    
    q.elementPush(2);
    q.printQueue();
    
    q.elementPush(3);
    q.printQueue();
    
    q.elementPush(4); // should drop 2
    q.printQueue();
    
    q.elementPop();
    q.printQueue();
    
    q.elementPop();
    q.printQueue();

    std::thread pop_thread([&q]() {
        int value = q.elementPop(); // will block as queue is empty
    });

    // Give the pop thread some time to start and block
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Push an element into the queue
    q.elementPush(4);

    // Wait for the pop thread to finish
    pop_thread.join();

    try {
        q.elementPopWithTimeout(1000);
        q.printQueue();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
    return 0;
}