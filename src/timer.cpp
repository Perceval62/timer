#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <exception>
#include <limits.h>
#include "timer.hpp"

//!Constructors
/**
 * \param name  unique name of the timer. Used for getting a description.
 * \param delay The interval at which the callback function is going to be
 *              called.
 * \param cb    The function to call at the given interval.
 * \param params Parameters to be given to the callback function
 */
timer::timer(std::string name, unsigned int delay, void (*cb)(void * p), void * params ):
    name(name),
    t1(NULL),
    activated(false),
    execDelay(delay),
    callback(cb),
    params(params)
{
    if(delay == 0)
    {
        delay = 100;
    }
}

timer::~timer()
{  
    this->stop();
}


/**
 * \return Return a string describing the state of the timer
 */
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
/**
 * Start the timer
 * \return Return a boolean representing the success or failure of the
 *          function.
 */
bool timer::start()
{
    //if no callback function was given
    if(this->callback == NULL)
    {
        return false;
    }
    // prevent integer overflow
    if(!(this->execDelay < UINT_MAX))    //! if the delay is not smaller than 
                                        //! the max value for int
    {
        return false;
    }
    

    std::mutex m;
    m.try_lock();
    bool ret = false;
    //if the object is already timing or callback hasnt been provided,
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
    m.unlock();
    return ret;
}
/**
 * Stops the timer
 * \return Return a boolean representing the success or failure of the
 *          function.
 */
bool timer::stop()
{
    //If the thread doesnt exist
    if(this->t1 == NULL)
    {
        return false;
    };
    
    std::mutex m;
    m.try_lock();
    //return value
    bool ret = false;
    try
    {    
        //Change the object's state
        this->activated = false;
        //Cleanup the thread
        this->t1->join();
        delete this->t1;
        //Resetting the pointer as available
        this->t1 = NULL;
        ret = true;
    }
    catch(const std::exception& e)
    {
        //Error handling with a stack trace
        std::cerr << e.what() << '\n';
        ret = false;
    }
    m.unlock();
    return ret;
}


/** 
* The routine that is spawned in the thread. 
* Waits for the amount of time (execDelay) and calls the callback
*/
void timer::count()
{
    while(this->activated != false)
    {
        std::chrono::milliseconds interval(execDelay);
        std::this_thread::sleep_for(interval);   
        this->callback(this->params);     
    }
}


/** Changes the name of the timer
 * \return Returns true if the change is successful
 */
void timer::setName(std::string newName)
{
    this->name = newName;
}

/** Gets the current name of the timer
 * \return Returns the current name of the timer
 */
std::string timer::getName()
{
    return this->name;
}

/** Gets the current state of the timer
 * \return True if the timer is activated
 */
bool timer::getState()
{
    return this->activated;
}

/** Gets the current delay of the timer
* \return True if the timer is activated
*/
unsigned int timer::getDelay()
{
   return this->execDelay;
}

/** Changes the current execution interval of the timer
 * \return True if the timer is activated
 */
bool timer::setDelay(unsigned int newDelay)
{
    //If object contains empty parameters
    if(this->callback == NULL)
    {
        this->execDelay = newDelay;
        return true;
    }

    //If callback as been given
    bool ret = false;
    if(this->stop() == true)
    {
        this->execDelay = newDelay;
        if(this->start() == true)
        {
            ret = true;
        }
    }
    return(ret);
}

/** Changes the current callback function of the timer
 * \return True if the timer is activated
 */
bool timer::setCallback(void (*cb)(void *), void * params)
{
    //If object contains empty parameters
    if(this->callback == NULL)
    {
        this->callback = cb;
        this->params = params;
        return true;
    }

    bool ret = false;
    if(this->stop() == true)
    {
        this->callback = cb;
        this->params = params;
        if(this->start() == true)
        {
            ret = true;
        }
    }
    return(ret);
}