#include <string>

class timerTestCase
{
    public:

        timerTestCase(bool isValid, std::string name, unsigned int delay, void (*cb)(void *), void * params);
        ~timerTestCase();

        bool testCombination();
        bool getTestValidity();

    private:
        bool isValid;
        std::string name;
        unsigned int delay;
        void (*cb)(void *);
        void * params;

};