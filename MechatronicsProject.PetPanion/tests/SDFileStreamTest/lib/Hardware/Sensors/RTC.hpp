#ifndef DEPS_H
    #define DEPS_H
    #include "../../deps.hpp"
#endif

//real time clock
class RTC
{
    private:
        //the RTC library that we're wrapping
        RTC_DS3231* _rtc;
    public:
        /*
        description: constructor
        inputs: none
        returns: instance of a real time clock object
        */
        RTC(void);
        /*
        description: sets up the RTC
        inputs: none
        returns: true if setup is successful
        */
        boolean Setup(void);
        /*
        description: adjusts the RTC to the date & time of
                     compilation
        inputs: a reference datetime for the clock to start at
        returns: none
        */
        void Adjust(DateTime);
        /*
        description: returns a true if the RTC lost power
        inputs: none
        returns: true if power was lost
        */
        boolean HasLostPower(void);
        /*
        description: returns the current date and time
        inputs: none
        returns: the current datetime
        */
        DateTime Now(void);
        /*
        description: returns the temperature in degrees celsius
        inputs: none
        returns: the temperature in degrees celsius
        */
        float GetTemperature(void);
};
