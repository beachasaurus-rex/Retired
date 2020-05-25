#ifndef ENUMS_H
    #define ENUMS_H
    #include "..\..\Enums.hpp"
#endif

//Holds configuration information for a color sensor.
typedef struct ColorSensorOptions
{
    //settings for the color sensor
    IntegrationTime IntTime;
    Gain ColorGain;
    //led pin for the color sensor
    byte LedPin;
    //default constructor
    ColorSensorOptions(void);

    /*
    description: constructor
    inputs:
        1. integration time setting for the color sensor
        2. gain setting for the color sensor
        3. LED pin number for the color sensor
    returns: instance of a color sensor options struct
    */
    ColorSensorOptions(IntegrationTime,
        Gain, byte);
} ColorSensorOptions;
