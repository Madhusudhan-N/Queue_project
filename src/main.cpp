#include <iostream>
#include <thread>
#include <chrono>
#include "elementQueue.h"

/**
 * @brief Writer function simulating push elements into the queue
 * @param q Reference to the queue.
 */
void writer(Queue<int>& q) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Ensure writer starts after main

    // Push sequence
    q.elementPush(1);
    q.printQueue();

    std::this_thread::sleep_for(std::chrono::milliseconds(300)); // Allow reader to pop 1

    q.elementPush(2);
    q.printQueue();

    q.elementPush(3);
    q.printQueue();

    q.elementPush(4); // 2 should be dropped
    q.printQueue();

    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate delay before pushing 5

    q.elementPush(5); // Unblock the reader
    q.printQueue();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    q.elementPush(6); // Unblock the reader
    q.printQueue();
}

/**
 * @brief Reader function simulating pop elements from the queue
 * @param q Reference to the queue.
 */
void reader(Queue<int>& q) {
    std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Allow writer to push first element

    // Pop 1
    q.elementPop();
    q.printQueue();

    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Ensure writer pushes 3 and 4

    // Pop 3
    q.elementPop();
    q.printQueue();

    // Pop 4
    q.elementPop();
    q.printQueue();

    std::cout << "Waiting for an element.. \n";
    
    // Block until writer pushes 5
    q.elementPop();
    std::cout << "Unblocked after push! \n";
    q.printQueue();

    // Block for 1s, writer pushes 6
    try {
        std::cout << "Waiting for element with timeout.. \n";
        q.elementPopWithTimeout(1000);
        std::cout << "Received element before timeout \n";
    }
        catch (const std::runtime_error& e) {
            std::cout << "Read thread: " << e.what() << std::endl;
        }
    
    // Block for 500ms, time out as no element was pushed
    try {
        std::cout << "Waiting for element with timeout.. \n";
        q.elementPopWithTimeout(500);
        std::cout << "Received element before timeout \n";
    }
        catch (const std::runtime_error& e) {
            std::cout << "Read thread: " << e.what() << std::endl;
        }


}

int main() {
    Queue<int> q(2); // Max size = 2

    std::thread writerThread(writer, std::ref(q));
    std::thread readerThread(reader, std::ref(q));

    writerThread.join();
    readerThread.join();

    std::cout << "Exit main \n";
    return 0;
}
