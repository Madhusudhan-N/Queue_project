#pragma once

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <chrono>

/** 
* A thread-safe queue that supports multi-threaded access
* @tparam T Type of elements stored in the queue
*/
template <typename T>
class Queue {

    T* m_data; /*< Dynamically allocated array for storing elements */
    int max_size, count, front, back;
    std::mutex m_mtx; /*< Mutex to ensure thread safety */
    std::condition_variable m_cv; /*< Condition variable for synchronization */

public:
    /** 
     * Constructor
     * @param size Maximum size of the queue
    */
    Queue(int size);
    
    /** 
     * Destructor
    */
    ~Queue();
    
    /**
     * Pushes an element into the queue
     * @param element The element to be added
    */
    void elementPush(T element);
    
    /**
     * Pops an element from the queue, blocking if empty
     * @return Removed element
    */
    T elementPop();
    
    /**
     * Pops an element with a timeout.
     * @param milliseconds Maximum time to wait before throwing an exception
     * @return Removed element if available within timeout
     * @throws std::runtime_error if timeout occurs
    */
    T elementPopWithTimeout(int milliseconds);
    
    /**
     * Returns the current number of elements in the queue
     * @return The number of elements
    */
    int elementCount();
    
    /**
     * Returns the maximum size of the queue
     * @return The queue capacity
    */
    int maxSize();
    
    /**
     * Prints the current elements in the queue
    */
    void printQueue();

}; // ELEMENTQUEUE_H
