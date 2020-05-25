#ifndef LYNX_MOTOR_H
    #define LYNX_MOTOR_H
    #include "LynxMotor.hpp"
#endif

//constructor
LynxMotor::LynxMotor(byte pin)
{
    this->_motor = new Servo();
    this->_pin = pin;

    //these hardcoded values come from Lab 5 Task 3
    this->_stop = 90;
}

//sets up the motor
void LynxMotor::Attach()
{
    //these hardcoded values come from Lab 5 Task 3
    this->_motor->attach(this->_pin, 1000, 2000);
}

//kills power to the motor
void LynxMotor::Detach()
{
    this->_motor->detach();
}

//stops the motor from rotating
void LynxMotor::Stop()
{
    this->_motor->write(this->_stop);
}

//returns true if motor is attached
boolean LynxMotor::IsAttached()
{
    return this->_motor->attached();
}

//rotates the lynx motor forward at the specified speed
void LynxMotor::RotateForward(int speed)
{
    this->_motor->write((this->_stop) + speed);
}

//rotates the lynx motor backward at the specified speed
void LynxMotor::RotateBackward(int speed)
{
    this->_motor->write((this->_stop) - speed);
}

//sets the duration of each PWM pulse in microseconds
void LynxMotor::SetPulseDuration(int ms)
{
    this->_motor->writeMicroseconds(ms);
}
