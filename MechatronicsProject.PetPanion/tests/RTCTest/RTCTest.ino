#ifndef PET_PANION_H
    #define PET_PANION_H
    #include "lib/PetPanion.hpp"
#endif

RTC* rtc;
DateTime now;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup()
{
    Serial.begin(9600);
    rtc = new RTC();

    if (!rtc->Setup())
    {
        Serial.println("RTC not found.");
        while (1);
    }

    //yes i know i didn't need the if blocks; i just wanted to show you how to implement adding in
    //a condition if the RTC happened to lose power
    if (rtc->HasLostPower())
    {
        //put in whatever time you want to set this to.
        //format = YEAR, MONTH, DAY, HOUR, MINUTE, SECOND
        rtc->Adjust(DateTime(2019, 1, 1, 0, 0, 0));
    }
    else
    {
      rtc->Adjust(DateTime(2019, 1, 1, 0, 0, 0));
    }
}

void loop()
{
    now = rtc->Now();

    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print('/');
    Serial.print(now.year(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
}
