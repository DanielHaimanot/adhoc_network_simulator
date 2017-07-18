cmake_minimum_required(VERSION 3.5)
project(Sim)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Network.cpp Network.h Node.cpp Node.h)
add_executable(Sim ${SOURCE_FILES})