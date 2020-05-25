#ifndef SERVO_MOTOR_OPTIONS_H
    #define SERVO_MOTOR_OPTIONS_H
    #include "ServoMotorOptions.hpp"
#endif

//constructor
ServoMotorOptions::ServoMotorOptions(byte pin, int minRot,
int maxRot)
{
    this->_pin = pin;
    this->_minRot = minRot;
    this->_maxRot = maxRot;
}

//gets the servo's pin number
byte ServoMotorOptions::GetPin()
{
    return this->_pin;
}

//gets the servo's minimum rotation
int ServoMotorOptions::GetMinRotation()
{
    return this->_minRot;
}

//gets the servo's maximum rotation
int ServoMotorOptions::GetMaxRotation()
{
    return this->_maxRot;
}
