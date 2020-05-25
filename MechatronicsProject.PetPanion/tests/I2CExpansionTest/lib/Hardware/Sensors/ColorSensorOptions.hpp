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
    //constructor
    ColorSensorOptions(IntegrationTime,
        Gain, byte);
} ColorSensorOptions;
