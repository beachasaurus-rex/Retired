#ifndef PET_PANION_H
    #define PET_PANION_H
    #include "lib/PetPanion.hpp"
#endif

LoadCell* loadCell;

void setup()
{
    Serial.begin(9600);
    loadCell = new LoadCell(7, 8, 128, -7050.0);

    if (!(loadCell->Setup()))
    {
        Serial.println("LoadCell isn't set up correctly.");
        while(1);
    }

    loadCell->Zero();
}

void loop()
{
    Serial.print(fabs(loadCell->Read()));
    Serial.println(" lbs");
}
