#ifndef RTC_H
    #define RTC_H
    #include "RTC.hpp"
#endif

//constructor
RTC::RTC()
{
    _rtc = new RTC_DS3231();
}

//sets up the RTC
boolean RTC::Setup()
{
    return _rtc->begin();
}

/*
adjusts the RTC to the date & time of
compilation
*/
void RTC::Adjust(DateTime input)
{
    _rtc->adjust(input);
}

//returns a true if the RTC lost power
boolean RTC::HasLostPower()
{
    return _rtc->lostPower();
}

//returns the current date and time
DateTime RTC::Now()
{
    return _rtc->now();
}

//returns the temperature in degrees celsius
float RTC::GetTemperature()
{
    return _rtc->getTemperature();
}
