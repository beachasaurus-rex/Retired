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
        //constructor
        RTC(void);
        //sets up the RTC
        boolean Setup(void);
        /*
        adjusts the RTC to the date & time of
        compilation
        */
        void Adjust(DateTime);
        //returns a true if the RTC lost power
        boolean HasLostPower(void);
        //returns the current date and time
        DateTime Now(void);
        //returns the temperature in degrees celsius
        float GetTemperature(void);
};
