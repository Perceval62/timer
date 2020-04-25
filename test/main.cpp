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

    std::array<timerTestCase, 5> testArray = {
        timerTestCase(false, "Test case 1", 1000, callbackExample, NULL),
        timerTestCase(false, "Test case 1", 1000, callbackExample, NULL), 
        timerTestCase(false, "Test case 1", 1000, callbackExample, NULL), 
        timerTestCase(false, "Test case 1", 1000, callbackExample, NULL),
        timerTestCase(false, "Test case 1", 1000, callbackExample, NULL)
        };


    for(auto i = testArray.begin(); i != testArray.end(); i++)
    {
        bool ret = i->testCombination();
        if(ret == i->getTestValidity())
        {
            std::cout <<"Test succeeded"<<std::endl;
        }
        else
        {
            std::cout <<"something unexpected occured"<<std::endl;
        }
        
    }   
}