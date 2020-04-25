cmake_minimum_required(VERSION 3.13)
project("timer") 

add_executable(timerTestExec src/main.cpp)
target_sources("timerTestExec" PRIVATE src/timer.cpp src/main.cpp)
find_package (Threads)

SET( CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread -Wall -Wpedantic" )
add_compile_options(-Wall -Wextra -pedantic -Werror)
INCLUDE_DIRECTORIES(include/)

add_library(timer SHARED src/timer.cpp)