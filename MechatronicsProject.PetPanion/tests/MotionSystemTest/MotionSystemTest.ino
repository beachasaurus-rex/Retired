#ifndef PET_PANION_H
    #define PET_PANION_H
    #include "lib/PetPanion.hpp"
#endif

MotionSystem* msys;

void setup()
{
    Wire.begin();
    Serial.begin(9600);

    //building the I2C expansion bus
    I2CExpansion* i2cExp = new I2CExpansion(1);

    //color sensor array options
    byte numSens = 3;
    byte ledPins[] = {22,23,24};
    byte cSenPorts[] = {0,1,2};
    IntegrationTime intTimes[] = {IT_101, IT_101, IT_101};
    Gain colorGains[] = {G_16x, G_16x, G_16x};
    ColorSensorArrayOptions csaOpts =
        ColorSensorArrayOptions(numSens, cSenPorts, intTimes,
            colorGains, ledPins);

    //building IR sensors
    IRSensor* irFront = new IRSensor(2);
    IRSensor* irBack = new IRSensor(3);

    //motion system options
    float csHigh = 150;
    float csLow = 100;
    float accErr = 2;
    int spdStr = 30;
    int spdSlowTurn = 30;
    int spdFastTurn = 50;
    MotionSystemOptions* msysOpts = new MotionSystemOptions(csHigh, csLow,
        spdStr, spdSlowTurn, spdFastTurn);

    //building the motion system
    byte leftPin = 4;
    byte rightPin = 5;
    msys = new MotionSystem(leftPin, rightPin, msysOpts, i2cExp, csaOpts,
        irFront, irBack);

    if (!(msys->Setup()))
    {
        Serial.println("Motion system didn't setup properly.");
        while(1);
    }
    msys->DeactivateLeds();
}

void loop()
{
    Serial.println("Going to feeding location.");
    msys->DebugGotoFeedingLocation();
    delay(5000);
    Serial.println("Going home.");
    msys->DebugGoHome();
    delay(5000);
}
