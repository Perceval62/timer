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