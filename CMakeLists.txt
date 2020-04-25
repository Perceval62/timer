cmake_minimum_required(VERSION 3.13)
project("timer") 

add_executable(timer src/main.cpp)
target_sources("timer" PRIVATE src/timer.cpp src/main.cpp)
find_package (Threads)

SET( CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread" )
INCLUDE_DIRECTORIES(include/)

