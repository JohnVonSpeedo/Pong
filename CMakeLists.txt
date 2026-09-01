cmake_minimum_required(VERSION 3.14)
project(Pong)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Pong source/main.cpp)

target_include_directories(Pong PRIVATE libs)