#include <iostream>
#include <string>
#include <chrono>
#include <thread>

/**
 * \class timer
 * \brief timer myTimer("myTimerName", 1000, myFunc)
 * 
 * This is an implementation of a timer in cpp. It is initialised with a callback function that is to be called at certain intervals
 * \author Vincent Perrier
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
         */
        timer(std::string name, unsigned int delay, void (*cb)());

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
        bool setCallback(void (*cb)());

    private:

        /** 
        * The routine that is spawned in the thread. 
        * Waits for the amount of time (execDelay) and calls the callback
        */
        void count();             

        std::string name;           /**< Unique name for this timer  */
        std::thread * t1;           /**< A space reserved for the thread that counts */
        volatile bool activated;    /**< Tells if the timer is running or stopped */
        
        unsigned int execDelay;     /**< The interval of time at which the callback is executed */
        void (*callback)();         /**< A pointer to the callback function */
};