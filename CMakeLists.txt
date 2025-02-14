cmake_minimum_required(VERSION 3.10)

project(Queue_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SOURCES src/*.cpp)

add_executable(Queue_project src/elementQueue.cpp src/main.cpp)

enable_testing()
add_subdirectory(test)
