
#MIT License
#
#Copyright (c) 2020 Vincent Perrier
#
#Permission is hereby granted, free of charge, to any person obtaining a copy
#of this software and associated documentation files (the "Software"), to deal
#in the Software without restriction, including without limitation the rights
#to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#copies of the Software, and to permit persons to whom the Software is
#furnished to do so, subject to the following conditions:
#
#The above copyright notice and this permission notice shall be included in all
#copies or substantial portions of the Software.
#
#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#SOFTWARE.


#CMAKE project description
cmake_minimum_required(VERSION 3.13)
project("timer") 

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