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

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <functional>

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
        timer(std::string name, unsigned int delay, std::function<void(void*)> cb, void * params);

        //!Destructor
        ~timer();

        /**
         * \return Return a string describing the state of the timer
         */
        std::string to_string();

        /**
         * Start the timer
         * \return Return a boolean representing the success or failure of the
         *          function.
         */
        bool start();

        /**
         * Stops the timer
         * \return Return a boolean representing the success or failure of the
         *          function.
         */
        bool stop();

        /** Changes the name of the timer
         * \return Returns true if the change is successful
         */
        void setName(std::string newName);

        /** Gets the current name of the timer
         * \return Returns the current name of the timer
         */
        std::string getName();

        /** Gets the current state of the timer
         * \return True if the timer is activated
         */
        bool getState();

        /** Gets the current delay of the timer
         * \return True if the timer is activated
         */
        unsigned int getDelay();

        /** Changes the current execution interval of the timer
         * \return True if the timer is activated
         */
        bool setDelay(unsigned int newDelay);

        /** Changes the current callback function of the timer
         * \return True if the timer is activated
         */
        bool setCallback(std::function<void(void*)>, void * params);

    private:

        /** 
        * The routine that is spawned in the thread. 
        * Waits for the amount of time (execDelay) and calls the callback
        */
        void count();             

        std::string name;           /**< Unique name for this timer  */
        std::thread * t1;           /**< A space reserved for the thread that counts */
        volatile bool activated;    /**< Tells if the timer is running or stopped */
        
        volatile unsigned int execDelay;     /**< The interval of time at which the callback is executed */
        std::function<void(void*)> callback;         /**< A pointer to the callback function */
        void * params;
};