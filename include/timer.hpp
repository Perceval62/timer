/*
MIT License

Copyright (c) 2020-2021 Vincent Perrier

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
#include <functional>
#include <atomic>
#include <climits>

/**
 * \class timer
 * \brief timer myTimer("myTimerName", 1000, myFunc)
 * 
 * This is an implementation of a timer in cpp. It is initialised with a callback function that is to be called at certain intervals
 * \author  Vincent Perrier
 * \date    25-04-2020 
 */
class timer
{
public:
    //!Constructors
    /**
         * \param name  unique name of the timer. Used for getting a description.
         * \param delay The interval at which the callback function is going to be
         *              called.
         * \param cb    The function to call at the given interval.
         * \param params Parameters to be given to the callback function
         */
    timer(std::string name, unsigned int delay, std::function<void(void *)> cb, void *params) : 
        name(name),
        t1(NULL),
        activated(false),
        execDelay(delay),
        callback(cb),
        params(params){
        if (delay == 0){
            delay = 100;
        }
    }
    //!Destructor
    ~timer(){
        this->stop();
    }

    /**
         * \return Return a string describing the state of the timer
         */
    std::string to_string(){
        std::string ret;
        std::string state;
        if (this->activated == true){
            state = "This timer is currently active";
        }
        else{
            state = "This timer is currently idle";
        }

        ret = this->name + " : a is set with a timer of " + std::to_string(this->execDelay) + "ms. " + state;
        return ret;
    }

    /**
         * Start the timer
         * \return Return a boolean representing the success or failure of the
         *          function.
         */
    bool start(){
        //if no callback function was given
        if (this->callback == NULL){
            return false;
        }
        // prevent integer overflow
        if (!(this->execDelay < UINT_MAX)){
            return false;
        }

        bool ret = false;
        //if the object is already timing or callback hasnt been provided,
        if (this->t1 != NULL){
            ret = false;
        }
        else{
            //Go ahead
            try{
                this->activated = true;
                t1 = new std::thread(&timer::count, this);
                ret = true;
            }
            catch (const std::exception &e){
                std::cerr << e.what() << '\n';
                ret = false;
            }
        }
        return ret;
    }

    /**
         * Stops the timer
         * \return Return a boolean representing the success or failure of the
         *          function.
         */
    bool stop(){
        //If the thread doesnt exist
        if (this->t1 == NULL){
            return false;
        };

        //return value
        bool ret = false;
        try{
            //Change the object's state
            this->activated = false;
            //Cleanup the thread
            this->t1->join();
            delete this->t1;
            //Resetting the pointer as available
            this->t1 = NULL;
            ret = true;
        }
        catch (const std::exception &e){
            //Error handling with a stack trace
            std::cerr << e.what() << '\n';
            ret = false;
        }
        return ret;
    }

    /** Changes the name of the timer
         * \return Returns true if the change is successful
         */
    void setName(std::string newName){
        this->name = newName;
    }

    /** Gets the current name of the timer
         * \return Returns the current name of the timer
         */
    std::string getName(){
        return this->name;
    }

    /** Gets the current state of the timer
         * \return True if the timer is activated
         */
    bool getState(){
        return this->activated;
    }

    /** Gets the current delay of the timer
         * \return True if the timer is activated
         */
    unsigned int getDelay(){
        return this->execDelay;
    }

    /** Changes the current execution interval of the timer
         * \return True if the timer is activated
         */
    bool setDelay(unsigned int newDelay){
        //If object contains empty parameters
        if (this->callback == NULL){
            this->execDelay = newDelay;
            return true;
        }

        //If callback as been given
        bool ret = false;
        if (this->stop() == true){
            this->execDelay = newDelay;
            if (this->start() == true){
                ret = true;
            }
        }
        return (ret);
    }

    /** Changes the current callback function of the timer
         * \return True if the timer is activated
         */
    bool setCallback(std::function<void(void *)> cb, void *params){
        //If object contains empty parameters
        if (this->callback == NULL){
            this->callback = cb;
            this->params = params;
            return true;
        }

        bool ret = false;
        if (this->stop() == true){
            this->callback = cb;
            this->params = params;
            if (this->start() == true){
                ret = true;
            }
        }
        return (ret);
    }

private:
    /** 
        * The routine that is spawned in the thread. 
        * Waits for the amount of time (execDelay) and calls the callback
        */
    void count(){
        while (this->activated != false){
            std::chrono::milliseconds interval(execDelay);
            std::this_thread::sleep_for(interval);
            this->callback(this->params);
        }
    }

    std::string name;            /**< Unique name for this timer  */
    std::thread *t1;             /**< A space reserved for the thread that counts */
    std::atomic<bool> activated; /**< Tells if the timer is running or stopped */

    std::atomic<unsigned int> execDelay;  /**< The interval of time at which the callback is executed */
    std::function<void(void *)> callback; /**< A pointer to the callback function */
    void *params;
};
