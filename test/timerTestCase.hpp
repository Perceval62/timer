#include <string>

class timerTestCase
{
    public:

        timerTestCase(bool isValid, std::string name, unsigned int delay, void (*cb)(void *), void * params);
        ~timerTestCase();

        bool testCombination();
        bool getTestValidity();

        std::string name;
        
    private:
        bool isValid;
        
        unsigned int delay;
        void (*cb)(void *);
        void * params;

};