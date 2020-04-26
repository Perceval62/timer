/*
MIT License

Copyright (c) 2020 Vincent Perrier

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
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