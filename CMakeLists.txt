#CMAKE project description
cmake_minimum_required(VERSION 3.13)
project("timer" 
        VERSION 1.0
        LANGUAGES C/C++) 

#specify the location of the header files
include_directories(include/)
#find the threads lib on the system
find_package (Threads)

#First target: Basic example of the timer lib
add_executable(timerExec ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_sources("timerExec" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/timer.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
add_compile_options(-Wall -Wextra -pedantic -Werror)
set( CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "--std=c++17 -pthread" )

#Second target: dynamic linked library of the timer lib.
add_library(timer SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/timer.cpp)

#Third target: unit tests for the lib (dynamically linked)
add_executable(testCases ${CMAKE_CURRENT_SOURCE_DIR}/test/main.cpp)
target_sources("testCases"
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/test/timerTestCase.cpp )
#Link the second target with the test executable.
target_link_libraries(testCases timer)

