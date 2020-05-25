#ifndef COLOR_SENSOR_OPTS_H
    #define COLOR_SENSOR_OPTS_H
    #include "ColorSensorOptions.hpp"
#endif

//default constructor
ColorSensorOptions::ColorSensorOptions() {}

//constructor
ColorSensorOptions::ColorSensorOptions(IntegrationTime intTime,
    Gain gain, byte ledPin)
{
    //set instance variables
    this->IntTime = intTime;
    this->ColorGain = gain;
    this->LedPin = ledPin;
}
