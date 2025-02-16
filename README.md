# Queue_project

## Project Overview
The project consists of the following components:

Queue Class: A thread-safe queue implemented as a circular buffer.

Push and Pop Functions: Thread-safe push and pop operations.

Blocking Pop: The pop function blocks indefinitely if the queue is empty.

Blocking with timeout Pop: The pop function blocks till given timeout if the queue is empty.

Test Program: A test program to verify the behavior of the queue, including lock release in the blocked state of pop.

### Dependencies

C++ Compiler: Supports C++11 or later (e.g., g++, clang++, or MSVC).

CMake version 3.10 or higher : For building the project using CMake.

### Build Instructions
```bash

#Clone the repo

git clone https://github.com/Madhusudhan-N/Queue_project.git
cd Queue_project

#Create a build directory and compile the project

mkdir build
cd build
cmake ..
make -j
```
### Running the project
``` bash 
#execute main
./Queue_project

#execute all google tests
./test/run_tests

#execute a single google test (example)
./test/run_tests --gtest_filter=QueueTest.PushPop
