cmake_minimum_required(VERSION 3.10)
project(risingCity)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SRC main.cpp RBT.cpp NodeBase.cpp Simulator.cpp MinHeap.cpp)

add_executable(risingCity ${SRC})