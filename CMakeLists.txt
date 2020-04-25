cmake_minimum_required(VERSION 3.13)
project("timer") 

include_directories(include/)
find_package (Threads)

add_executable(timerExec ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_sources("timerExec" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/timer.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
add_compile_options(-Wall -Wextra -pedantic -Werror)
set( CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "--std=c++17 -pthread" )

add_library(timer SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/timer.cpp)

add_executable(testCases ${CMAKE_CURRENT_SOURCE_DIR}/test/main.cpp)
target_sources("testCases"
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/test/timerTestCase.cpp )
target_link_libraries(testCases timer)

