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

#include <assert.h>

#include <iostream>
#include <vector>

void callbackExample(void *)
{
    std::cout << "callback func"<<std::endl;
}

int main()
{
    std::cout<<"Starting testing of the module timer"<<std::endl;

    int example = 5;

    std::array<timerTestCase, 5> testArray = {
        timerTestCase(true, "Test case 1", 1000, callbackExample, NULL),
        timerTestCase(false, "", 1000, NULL, NULL), 
        timerTestCase(true, "Test case 1", 0, callbackExample, &example), 
        timerTestCase(true, "ésad128bfkjse", 1000, callbackExample, NULL),
        timerTestCase(false, "validTimer", -1, callbackExample, NULL)

        //* ... Declare new test cases here *//

        };


    for(auto i = testArray.begin(); i != testArray.end(); i++)
    {
        std::cout <<"===============" + i->name +"==============="<<std::endl;
        bool ret = i->testCombination();
        if(ret == i->getTestValidity())
        {
            std::cout <<"===============Test succeeded==============="<<std::endl;
        }
        else
        {
            std::cout <<"===============Test Failed==============="<<std::endl;
        }
        
    }   
}