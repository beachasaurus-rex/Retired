#ifndef SERVO_MOTOR_OPTIONS_H
    #define SERVO_MOTOR_OPTIONS_H
    #include "ServoMotorOptions.hpp"
#endif

//constructor
ServoMotorOptions::ServoMotorOptions(byte pin)
{
    this->_pin = pin;
}

//gets the servo's pin number
byte ServoMotorOptions::GetPin()
{
    return this->_pin;
}
