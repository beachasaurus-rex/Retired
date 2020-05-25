#ifndef COLOR_SENSOR_H
    #define COLOR_SENSOR_H
    #include "ColorSensor.hpp"
#endif

#ifndef I2C_EXP_H
    #define I2C_EXP_H
    #include "I2CExpansion.hpp"
#endif

#ifndef COLOR_SENSOR_OPTS_H
    #define COLOR_SENSOR_OPTS_H
    #include "ColorSensorOptions.hpp"
#endif

#ifndef COLOR_SENSOR_ARR_OPTS_H
    #define COLOR_SENSOR_ARR_OPTS_H
    #include "ColorSensorArrayOptions.hpp"
#endif

class ColorSensorArray
{
    private:
        //the number of sensors in the array
        byte _numSens;
        //array of pointers to ColorSensor objects
        ColorSensor** _senArr;
        //the i2c expansion bus
        I2CExpansion* _i2cBus;
        /*
        the i2c bus ports that the color sensors are
        connected to
        */
        byte* _senPorts;

    public:
        /*
        constructor
        inputs:
            1: i2c bus connection ports of each color sensor
            2: options for the array
        */
        ColorSensorArray(I2CExpansion*,
            ColorSensorArrayOptions);
        /*
        sets up the sensor array
        */
        boolean Setup(void);
        /*
        returns an array of RGB values for each sensor in the array.
        */
        float** ReadRGBValues(void);
        /*
        returns an array of RGB values for each sensor in the array
        and blinks each sensor's LED after it reads
        */
        float** TestReadRGBValues(void);
        /*
        returns the number of sensors in the array
        */
        int Count(void);
        /*
        turns on all sensor LEDs in the array
        */
        void ActivateLeds(void);
        /*
        turns off all sensor LEDs in the array
        */
        void DeactivateLeds(void);
        /*
        turns on a sensor's LED in the array
        */
        void ActivateLed(byte sensorNumber);
        /*
        turns off a sensor's LED in the array
        */
        void DeactivateLed(byte sensorNumber);
};
