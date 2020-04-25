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
    delete this->t1;
}

std::string timer::to_string()
{
    std::string ret;
    ret = this->name + " : a is set with a timer of " + std::to_string(this->execDelay);
    return ret;
}

bool timer::activate()
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
            ret = false;
        }
    }
    return ret;
}

bool timer::stop()
{
    bool ret = false;
    try
    {    
        if(t1 != NULL)
        {
            this->activated = false;
            t1->join();
        }
    }
    catch(const std::exception& e)
    {
        //std::cerr << e.what() << '\n';
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