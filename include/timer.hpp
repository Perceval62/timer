#include <iostream>
#include <string>
#include <chrono>
#include <thread>


/**
 * \class timer
 *
 * \brief timer myTimer("myTimerName", 1000, myFunc)
 *
 * This is an implementation of a timer in cpp.
 *
 * \note The delay parameter is in milliseconds.
 *
 * \author Vincent Perrier
 * 
 */
class timer
{
    public:
        //Constructors
    
        timer(std::string name, int delay, void (*cb)());

        //Destructor
        ~timer();

        std::string to_string();
        bool start();
        bool stop();
        


    private:

        std::string name;   //useful for comparing objects
        std::thread * t1;    
        volatile bool activated;
        void count();
        int execDelay;
        void (*callback)();
};