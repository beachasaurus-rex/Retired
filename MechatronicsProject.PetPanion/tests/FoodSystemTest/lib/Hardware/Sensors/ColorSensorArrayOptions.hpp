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

    /*
    description: constructor
    inputs:
        1. the number of sensors to be built
        2. an array of the I2C bus connection port numbers for each sensor
        3. the integration time settings for each sensor
        4. the gain settings for each sensor
        5. the LED pin number for each sensor
    returns: instance of a color sensor array options struct
    */
    ColorSensorArrayOptions(byte, byte*,
        IntegrationTime*, Gain*, byte*);
} ColorSensorArrayOptions;
