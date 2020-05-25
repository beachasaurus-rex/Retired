#ifndef PET_PANION_H
    #define PET_PANION_H
    #include "lib/PetPanion.hpp"
#endif

FoodSystem* fsys;

void setup()
{
    Serial.begin(9600);

    //setting servo options
    byte pin = 6;
    ServoMotorOptions* servOpts = new ServoMotorOptions(pin);

    //setting load cell options
    byte dOutPin = 7;
    byte sClockPin = 8;
    byte gain = 128;
    float calibFac = -7050.0;
    LoadCellOptions* lcOpts = new LoadCellOptions(dOutPin, sClockPin,
        gain, calibFac);

    //building the food system
    int degsOpen = 0;
    int degsClose = 75;
    float weightSP = 0.25;
    float errTol = 0.1;
    long minDelay = 150;
    long initDelay = 2500;
    fsys = new FoodSystem(degsOpen, degsClose, weightSP, errTol,
        minDelay, initDelay, lcOpts, servOpts);

    if (!(fsys->Setup()))
    {
        Serial.println("Food system isn't setup correctly.");
        while(1);
    }

    fsys->ZeroScale();
}

void loop()
{
    fsys->DispenseFood();
    Serial.println("Dispensing finished.");

    Serial.print("Food weight: ");
    Serial.print(fsys->GetLastMeasuredWeight());
    Serial.println(" lbs");
    while(1);
}
