#include "timerTestCase.hpp"
#include "timer.hpp"
#include <string>
#include <string.h>
#include <assert.h>

timerTestCase::timerTestCase(bool isValid, std::string name, unsigned int delay, void (*cb)(void *), void * params):
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