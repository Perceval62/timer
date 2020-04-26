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

#include "timerTestCase.hpp"
#include "timer.hpp"
#include <string>
#include <string.h>
#include <assert.h>

timerTestCase::timerTestCase(bool isValid, std::string name, unsigned int delay, std::function<void(void*)> cb, void * params):
        name(name),
        isValid(isValid),
        delay(delay),
        cb(cb),
        params(params)
{

}

timerTestCase::~timerTestCase()
{
}

bool timerTestCase::testCombination()
{
    try
    {
        std::cout<<"Starting test case for timer"<<std::endl;

        timer myTimer("", 1, NULL, NULL);
        if(myTimer.start() == true)
        {
            std::cout <<"start succeeded when nothing is initialised"<<std::endl;
            return false;
        }

        if(myTimer.getState() == true)
        {
            std::cout <<"undefined state, shouldnt succeed"<<std::endl;
            return false;
        }

        myTimer.setName(this->name);
        if( strcmp(myTimer.getName().c_str(), this->name.c_str()) != 0)
        {
            std::cout <<"Name doesnt match given value"<<std::endl;
            return false;
        }
        if(myTimer.setDelay(this->delay) == false)
        {
            std::cout <<"Couldnt set delay"<<std::endl;
            return false;
        }
        if(myTimer.setCallback(this->cb, this->params) == false)
        {
            std::cout <<"Could not set new callback "<<std::endl;
            return false;
        }
        if(myTimer.start() == false)
        {
            std::cout <<"Start did not succeed "<<std::endl;
            return false;
        }
        else
        {
            std::cout <<"Start succeed "<<std::endl;
        }
        

        if( myTimer.getDelay() != this->delay)
        {
            std::cout <<"Delay getter doesnt match given value"<<std::endl;
            return false;
        }
        
        if(myTimer.getState() != true)
        {
             std::cout <<"State getter doesnt match given value"<<std::endl;
            return false;
        }

        if(myTimer.stop() == false)
        {
            std::cout <<"Could not stop the timer"<<std::endl;
            return false;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return true;
}

bool timerTestCase::getTestValidity()
{
    return this->isValid;
}