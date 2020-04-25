#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <array>
#include "timer.hpp"

void myCallback(void *)
{
    std::cout << "Callback" <<std::endl;
}

int main(int argc, char ** argv) 
{
    timer timer1("timer1", 1000, myCallback, NULL);
    timer1.start();
    for (int i = 0; i <= 10; i++)
    {
        std::cout << "Doing stuff" <<std::endl;
        std::chrono::milliseconds interval(500);
        std::this_thread::sleep_for(interval);
        if(i == 5)
        {
            timer1.stop();
            std::cout << "Stopping timer 1" <<std::endl;
        }
    }
    std::cout << "End of the timer1 loop" <<std::endl;

    timer timer2("timer2", 200, myCallback, NULL);
    timer2.start();
    for(int i =0; i< 5; i++)
    {
        std::chrono::milliseconds interval(500);
        std::this_thread::sleep_for(interval);
    }
    std::cout << timer2.to_string() <<std::endl;
    timer2.stop();

    std::cout << "Finished with timer2, restarting timer1"<<std::endl;
    if(!timer1.start()){std::cout << "Couldn't start the timer"<<std::endl;}
    for(int i =0; i< 5; i++)
    {
        std::chrono::milliseconds interval(1000);
        std::this_thread::sleep_for(interval);
        std::cout << "Doing stuff" <<std::endl;
    }

    return 0;
}