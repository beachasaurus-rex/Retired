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
        the i2c bus ports that are connected to
        the color sensors
        */
        byte* _senPorts;

    public:
        /*
        description: constructor
        inputs:
            1: pointer to the I2C expansion bus
            2: options for the array
        returns: instance of a ColorSensorArray object
        */
        ColorSensorArray(I2CExpansion*,
            ColorSensorArrayOptions);
        /*
        description: sets up the sensor array
        inputs: none
        returns: true if setup is successful
        */
        boolean Setup(void);
        /*
        description: returns an array of RGB values for each sensor in the
                     array.
        inputs: none
        returns: an array of RGB arrays
        */
        float** ReadRGBValues(void);
        /*
        description: returns an array of RGB values for each sensor in the array
                     and blinks each sensor's LED after it reads
        inputs: none
        returns: an array of RGB arrays
        */
        float** TestReadRGBValues(void);
        /*
        description: returns the number of sensors in the array
        inputs: none
        returns the number of color sensors in the array
        */
        int Count(void);
        /*
        description: turns on all sensor LEDs in the array
        inputs: none
        returns: none
        */
        void ActivateLeds(void);
        /*
        description: turns off all sensor LEDs in the array
        inputs: none
        returns: none
        */
        void DeactivateLeds(void);
        /*
        description: turns on a sensor's LED in the array
        inputs: the color sensor number
        returns: none
        */
        void ActivateLed(byte sensorNumber);
        /*
        description: turns off a sensor's LED in the array
        inputs: the color sensor number
        returns: none
        */
        void DeactivateLed(byte sensorNumber);
};
