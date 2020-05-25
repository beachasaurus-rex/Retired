#ifndef SERVO_MOTOR_H
    #define SERVO_MOTOR_H
    #include "ServoMotor.hpp"
#endif

//constructor
ServoMotor::ServoMotor(byte pin)
{
    this->_motor = new Servo();
    this->_pin = pin;
}

//sets up the motor
void ServoMotor::Attach()
{
    this->_motor->
        attach(this->_pin);
}

//kills power to the motor
void ServoMotor::Detach()
{
    this->_motor->detach();
}

//returns true if motor is attached
boolean ServoMotor::IsAttached(void)
{
    return this->_motor->attached();
}

//rotates the servo the input amount of degrees
void ServoMotor::Rotate(int deg)
{
    this->_motor->write(deg);
}

//sets the duration of each PWM pulse in microseconds
void ServoMotor::SetPulseDuration(int ms)
{
    this->_motor->writeMicroseconds(ms);
}
