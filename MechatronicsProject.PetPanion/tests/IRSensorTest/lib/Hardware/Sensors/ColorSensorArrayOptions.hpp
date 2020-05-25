#ifndef ENUMS_H
    #define ENUMS_H
    #include "..\..\Enums.hpp"
#endif

#ifndef COLOR_SENSOR_OPTS_H
    #define COLOR_SENSOR_OPTS_H
    #include "ColorSensorOptions.hpp"
#endif

/*
An array of options that holds configuration
information for a predetermined number of
color sensors.
*/
typedef struct ColorSensorArrayOptions
{
    //I2C bus port numbers
    byte* I2CPorts;
    //array of color sensor options
    ColorSensorOptions* SensorOptions;
    //number of sensors in the array
    byte NumberOfSensors;
    //constructor
    ColorSensorArrayOptions(byte, byte*,
        IntegrationTime*, Gain*, byte*);
} ColorSensorArrayOptions;
