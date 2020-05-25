#ifndef COLOR_SENSOR_ARR_H
    #define COLOR_SENSOR_ARR_H
    #include "ColorSensorArray.hpp"
#endif

//constructor
ColorSensorArray::ColorSensorArray(I2CExpansion* i2cBus,
    ColorSensorArrayOptions opts)
{
    //set instance variables
    this->_i2cBus = i2cBus;
    this->_numSens = opts.NumberOfSensors;
    this->_senPorts = new byte[this->_numSens];

    /*
    build color sensors and store their pointers
    into an array
    */
    ColorSensor** sens = new ColorSensor*[this->_numSens];
    for (int i = 0; i < this->_numSens; i++)
    {
        ColorSensorOptions curOpts = opts.SensorOptions[i];

        sens[i] = new ColorSensor(curOpts.IntTime,
            curOpts.ColorGain, curOpts.LedPin);
        this->_senPorts[i] = opts.I2CPorts[i];
    }

    //store the pointer array
    this->_senArr = sens;
}

/*
returns the number of sensors in the array
*/
int ColorSensorArray::Count()
{
    return this->_numSens;
}

/*
starts the sensor array
*/
boolean ColorSensorArray::Setup()
{
    boolean allStarted = true;

    /*
    iterates through each color sensor and
    starts each one
    */
    for (int i = 0; i < this->_numSens; i++)
    {
        byte curPort = this->_senPorts[i];
        ColorSensor* curSen = this->_senArr[i];

        this->_i2cBus->SelectPort(curPort);

        if (!(curSen->Setup()))
        {
            allStarted = false;
            Serial.print("Color Sensor ");
            Serial.print(i);
            Serial.println(" couldn't start properly.");
        }
    }

    return allStarted;
}

/*
returns an array of RGB values for
each sensor in the array.
*/
float** ColorSensorArray::ReadRGBValues()
{
    //preallocate a pointer array
    float** rgbArrs = new float*[this->_numSens];

    /*
    iterate through each sensor and store
    their RGB array into the pointer array
    */
    for (int i = 0; i < this->_numSens; i++)
    {
        byte curPort = this->_senPorts[i];
        Serial.println(curPort);

        this->_i2cBus->SelectPort(curPort);
        rgbArrs[i] = this->_senArr[i]->GetRGB();
    }

    //return the pointer array
    return rgbArrs;
}

/*
returns an array of RGB values for each sensor in the array
and blinks each sensor's LED after it reads
*/
float** ColorSensorArray::TestReadRGBValues()
{
    //preallocate a pointer array
    float** rgbArrs = new float*[this->_numSens];

    /*
    iterate through each sensor and store
    their RGB array into the pointer array.
    toggles the LED on and off after reading.
    */
    for (int i = 0; i < this->_numSens; i++)
    {
        byte curPort = this->_senPorts[i];
        ColorSensor* curSen = this->_senArr[i];

        this->_i2cBus->SelectPort(curPort);
        rgbArrs[i] = curSen->GetRGB();

        this->DeactivateLed(i+1);
        delay(200);
        this->ActivateLed(i+1);
    }

    //return the pointer array
    return rgbArrs;
}

/*
turns on all sensor LEDs in the array
*/
void ColorSensorArray::ActivateLeds()
{
    for (int i = 0; i < this->_numSens; i++)
    {
        this->_senArr[i]->LedOn();
    }
}

/*
turns off all sensor LEDs in the array
*/
void ColorSensorArray::DeactivateLeds()
{
    for (int i = 0; i < this->_numSens; i++)
    {
        this->_senArr[i]->LedOff();
    }
}

/*
turns on a sensor's LED in the array
*/
void ColorSensorArray::ActivateLed(byte sensorNumber)
{
    this->_senArr[sensorNumber - 1]->LedOn();
}

/*
turns off a sensor's LED in the array
*/
void ColorSensorArray::DeactivateLed(byte sensorNumber)
{
    this->_senArr[sensorNumber - 1]->LedOff();
}
