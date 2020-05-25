#ifndef PET_PANION_H
    #define PET_PANION_H
    #include "lib/PetPanion.hpp"
#endif

IRSensor* irSen;

void setup()
{
    Serial.begin(9600);
    irSen = new IRSensor(34);

    if (!(irSen->Setup()))
    {
        Serial.println("IRSensor isn't setup correctly.");
    }
}

void loop()
{
    if (irSen->FoundObstacle())
    {
        Serial.println("Obstacle detected.");
    }
}
