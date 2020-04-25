#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "timer.hpp"

timer::timer(std::string name, int delay, void (*cb)()):
    name(name),
    t1(NULL),
    activated(false),
    execDelay(delay),
    callback(cb)
{
    if(delay == 0)
    {
        delay = 1;
    }
}

timer::~timer()
{  
    this->stop();
}

std::string timer::to_string()
{
    std::string ret;
    std::string state;
    if(this->activated == true)
    {
        state = "This timer is currently active";
    }
    else
    {
        state = "This timer is currently idle";
    }
    
    ret = this->name + " : a is set with a timer of " + std::to_string(this->execDelay) + "ms. " + state ;
    return ret;
}

bool timer::start()
{

    bool ret = false;
    //if the object is already timing,
    if(this->t1 != NULL)
    {
        ret = false;
    }
    else
    {
        //Go ahead
        try
        {
            this->activated = true;
            t1 = new std::thread(&timer::count, this);
            ret = true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            ret = false;
        }
    }
    return ret;
}

bool timer::stop()
{
    //return value
    bool ret = false;
    try
    {    
        if(t1 != NULL)
        {
            //Change the object's state
            this->activated = false;
            //Cleanup the thread
            this->t1->join();
            delete this->t1;

            //Resetting the pointer as available
            this->t1 = NULL;
        }
    }
    catch(const std::exception& e)
    {
        //Error handling with a stack trace
        std::cerr << e.what() << '\n';
        ret = false;
    }
    return ret;
}

void timer::count()
{
    while(this->activated != false)
    {
        std::chrono::milliseconds interval(execDelay);
        std::this_thread::sleep_for(interval);   
        this->callback();     
    }
}