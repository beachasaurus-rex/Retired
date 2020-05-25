#ifndef COLOR_SENSOR_ARR_OPTS_H
    #define COLOR_SENSOR_ARR_OPTS_H
    #include "ColorSensorArrayOptions.hpp"
#endif

//constructor
ColorSensorArrayOptions::ColorSensorArrayOptions(
    byte numSensors, byte* i2cPorts,
    IntegrationTime* intTimes, Gain* colorGains,
    byte* ledPins)
{
    //set instance variables
    this->I2CPorts = i2cPorts;
    this->NumberOfSensors = numSensors;

    //preallocate an array of ColorSensorOptions
    ColorSensorOptions* opts = new ColorSensorOptions[numSensors];

    /*
    iterate through the number of sensors to be made
    and create options for each sensor. afterwards,
    store those options into the array.
    */
    for (int i = 0; i < numSensors; i++)
    {
        opts[i] = ColorSensorOptions(intTimes[i], colorGains[i],
            ledPins[i]);
    }

    /*
    store the options array into an instance
    variable
    */
    this->SensorOptions = opts;
}
