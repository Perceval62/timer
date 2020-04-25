#include "timerTestCase.hpp"
#include "timer.hpp"
#include <string>
#include <string.h>
#include <assert.h>

timerTestCase::timerTestCase(bool isValid, std::string name, unsigned int delay, void (*cb)(void *), void * params):
        isValid(isValid),
        name(name),
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
        timer myTimer("", 1, NULL, NULL);
        if(myTimer.start() == true || myTimer.getState() == true)
        {
            std::cout <<"undefined state, shouldnt succeed"<<std::endl;
            return false;
        }
        myTimer.setName(this->name);
        if( strcmp(myTimer.getName().c_str(), this->name.c_str()) != 0)
        {
            return false;
        }
        if(myTimer.setDelay(this->delay) == false)
        {
            return false;
        }
        if(myTimer.setCallback(this->cb, this->params) == false)
        {
            return false;
        }
        if(myTimer.start() != true)
        {
            return false;
        }

        if( myTimer.getDelay() != this->delay)
        {
            return false;
        }

        if(myTimer.getState() != true)
        {
            return false;
        }

        if(myTimer.stop() == false)
        {
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