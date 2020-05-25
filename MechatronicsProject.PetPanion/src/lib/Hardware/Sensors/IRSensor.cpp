#ifndef IR_SENSOR_H
    #define IR_SENSOR_H
    #include "IRSensor.hpp"
#endif

//constructor
IRSensor::IRSensor(byte pin)
{
    this->_pin = pin;
}

//sets up the IR sensor
boolean IRSensor::Setup()
{
    pinMode(this->_pin, INPUT);
    return true;
}

//returns true if obstacle is found
boolean IRSensor::FoundObstacle(void)
{
    return !(digitalRead(this->_pin));
}

byte IRSensor::GetPinNumber()
{
    return this->_pin;
}
