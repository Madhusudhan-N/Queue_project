#include <gtest/gtest.h>
#include <thread>
#include "elementQueue.h"

TEST(QueueTest, PushPop) {
    Queue<int> queue(2);
    queue.elementPush(1);
    queue.elementPush(2);
    EXPECT_EQ(queue.elementCount(), 2);
    EXPECT_EQ(queue.elementPop(), 1);
    EXPECT_EQ(queue.elementPop(), 2);
    EXPECT_EQ(queue.elementCount(), 0);
}

TEST(QueueTest, PushFull) {
    Queue<int> queue(2);
    queue.elementPush(1);
    queue.elementPush(2);
    queue.elementPush(3); // Should drop 1
    EXPECT_EQ(queue.elementCount(), 2);
    EXPECT_EQ(queue.elementPop(), 2);
    EXPECT_EQ(queue.elementPop(), 3);
}

TEST(QueueTest, PopTimeoutError) {
    Queue<int> queue(2);
    EXPECT_THROW(queue.elementPopWithTimeout(100), std::runtime_error);
}

TEST(QueueTest, PopTimeoutNoError) {
    Queue<int> queue(2);

    std::thread push_thread([&queue]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // delay to trigger pop
        queue.elementPush(10); // push before timeout
    });

    EXPECT_NO_THROW(queue.elementPopWithTimeout(1000));

    push_thread.join();
}
