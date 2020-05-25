#ifndef PET_PANION_H
    #define PET_PANION_H
    #include "lib/PetPanion.hpp"
#endif

Clock* clock;
I2CExpansion* i2c;
DateTime now;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup()
{
    Wire.begin();
    Serial.begin(9600);
    
    byte clockPort = 3;
    i2c = new I2CExpansion(1);
    clock = new Clock(i2c, clockPort);

    if (!clock->Setup())
    {
        Serial.println("Clock not found.");
        while (1);
    }

    //yes i know i didn't need the if blocks; i just wanted to show you how to implement adding in
    //a condition if the clock happened to lose power
    if (clock->HasLostPower())
    {
        //put in whatever time you want to set this to.
        //format = YEAR, MONTH, DAY, HOUR, MINUTE, SECOND
        clock->Adjust(DateTime(2019, 1, 1, 0, 0, 0));
    }
    else
    {
      clock->Adjust(DateTime(2019, 1, 1, 0, 0, 0));
    }
}

void loop()
{
    now = clock->Now();

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
