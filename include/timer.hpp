#include <iostream>
#include <string>
#include <chrono>
#include <thread>


/*
*   @author Vincent Perrier
*   @desc   Implementation of a timer with a callback function.
*/
class timer
{
    public:
        //Constructors
        timer(std::string name, int delay, void (*cb)());

        //Destructor
        ~timer();

        std::string to_string();
        bool activate();
        bool stop();
        


    private:
        std::string name;   //useful for comparing objects
        std::thread * t1;    
        volatile bool activated;
        void count();
        int execDelay;
        void (*callback)();
};