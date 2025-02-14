#include <iostream>
#include "elementQueue.h"
#include <thread>

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

    
    try {
        q.elementPopWithTimeout(1000);
        q.printQueue();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
    q.elementPush(5);
    q.printQueue();
    
    q.elementPop();
    q.printQueue();
    
    return 0;
}