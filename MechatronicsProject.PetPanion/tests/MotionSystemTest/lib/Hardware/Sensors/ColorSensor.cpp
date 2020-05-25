#ifndef COLOR_SENSOR_H
    #define COLOR_SENSOR_H
    #include "ColorSensor.hpp"
#endif

//constructor
ColorSensor::ColorSensor(IntegrationTime intTime, Gain gain,
    byte ledPin)
{
    //set instance variables
    this->_sen = new Adafruit_TCS34725();
    this->_ledPin = ledPin;

    //set the current integration time
    this->SetIntegrationTime(intTime);
    //set the current gain
    this->SetGain(gain);
}

//sets up the sensor
boolean ColorSensor::Setup()
{
    pinMode(this->_ledPin, OUTPUT);
    return this->_sen->begin();
}

//enables the sensor
void ColorSensor::Enable()
{
    this->_sen->enable();
}

//disables the sensor
void ColorSensor::Disable()
{
    this->_sen->disable();
}

//removes any interrupts from the sensor
void ColorSensor::ClearInterrupts()
{
    this->_sen->clearInterrupt();
}

//returns an array of RGB values
float* ColorSensor::GetRGB()
{
    float r;
    float g;
    float b;
    this->_sen->getRGB(&r, &g, &b);

    float* arr = new float[3];
    arr[0] = r;
    arr[1] = g;
    arr[2] = b;
    return arr;
}

//returns the color temperature
uint16_t ColorSensor::GetColorTemperature(float* rgb)
{
    return this->_sen->calculateColorTemperature(rgb[0],
        rgb[1], rgb[2]);
}

//returns the lux (brightness)
uint16_t ColorSensor::GetLux(float* rgb)
{
    return this->_sen->calculateLux(rgb[0], rgb[1], rgb[2]);
}

//gets a pointer to the current setting for gain
tcs34725Gain_t* ColorSensor::GetGain()
{
    return &(this->_gain);
}

//sets the gain setting
void ColorSensor::SetGain(Gain gain)
{
    switch (gain)
    {
        case G_1x:
            this->_gain = TCS34725_GAIN_1X;
            break;
        case G_4x:
            this->_gain = TCS34725_GAIN_4X;
            break;
        case G_16x:
            this->_gain = TCS34725_GAIN_16X;
            break;
        case G_60x:
            this->_gain = TCS34725_GAIN_60X;
            break;
    }

    this->_sen->setGain(this->_gain);
}

//gets a pointer to the current setting for
//the integral time
tcs34725IntegrationTime_t* ColorSensor::GetIntegrationTime()
{
    return &(this->_intTime);
}

//sets the integral time
void ColorSensor::SetIntegrationTime(IntegrationTime intTime)
{
    switch (intTime)
    {
        case IT_2_4:
            this->_intTime = TCS34725_INTEGRATIONTIME_2_4MS;
            break;
        case IT_24:
            this->_intTime = TCS34725_INTEGRATIONTIME_24MS;
            break;
        case IT_50:
            this->_intTime = TCS34725_INTEGRATIONTIME_50MS;
            break;
        case IT_101:
            this->_intTime = TCS34725_INTEGRATIONTIME_101MS;
            break;
        case IT_154:
            this->_intTime = TCS34725_INTEGRATIONTIME_154MS;
            break;
        case IT_700:
            this->_intTime = TCS34725_INTEGRATIONTIME_700MS;
            break;
    }

    this->_sen->setIntegrationTime(this->_intTime);
}

//sets the pin for the led
void ColorSensor::SetLedPin(byte pin)
{
    this->_ledPin = pin;
}

//turns the LED on
void ColorSensor::LedOn()
{
    digitalWrite(this->_ledPin, HIGH);
}

//turns the LED off
void ColorSensor::LedOff()
{
    digitalWrite(this->_ledPin, LOW);
}
