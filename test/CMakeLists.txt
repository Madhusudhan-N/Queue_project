cmake_minimum_required(VERSION 3.10)

# Fetch GoogleTest if not already present
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Set testing framework
add_executable(run_tests test_queue.cpp ../src/elementQueue.cpp)
target_link_libraries(run_tests gtest gtest_main)

add_test(NAME QueueTest COMMAND run_tests)