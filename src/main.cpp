#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <array>
#include "timer.hpp"

void bruh()
{
    std::cout << "bruh" <<std::endl;
}

int main(int argc, char ** argv) 
{
    timer timer1("timer1", 1000, bruh);
    timer1.activate();

    for (int i = 0; i <= 10; i++)
    {
        std::cout << "Doing sum shit" <<std::endl;
        std::chrono::milliseconds interval(500);
        std::this_thread::sleep_for(interval);
        if(i == 5)
        {
            timer1.stop();
        }
    }

    timer timer2("timer2", 200, bruh);
    std::cout << timer2.to_string() <<std::endl;
    timer2.activate();
    for(int i =0; i< 5; i++)
    {
        std::chrono::milliseconds interval(500);
        std::this_thread::sleep_for(interval);
    }
    return 0;
}