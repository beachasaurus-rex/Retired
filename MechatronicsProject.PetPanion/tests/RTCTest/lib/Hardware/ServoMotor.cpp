#ifndef SERVO_MOTOR_H
    #define SERVO_MOTOR_H
    #include "ServoMotor.hpp"
#endif

//constructor
ServoMotor::ServoMotor(byte pin, int minRotation, int maxRotation)
{
    this->_motor = new Servo();
    this->_pin = pin;
    this->_minRot = minRotation;
    this->_maxRot = maxRotation;
}

//sets up the motor
void ServoMotor::Attach()
{
    this->_motor->
        attach(this->_pin, this->_minRot, this->_maxRot);
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
    int curPos = this->_curPos;
    int newPos = curPos + deg;
    boolean outRange =
        (newPos > this->_maxRot) ||
        (newPos < this->_minRot);

    if (!outRange)
    {
        this->_motor->write(deg);
        this->_curPos = newPos;
    }
}

//sets the duration of each PWM pulse in microseconds
void ServoMotor::SetPulseDuration(int ms)
{
    this->_motor->writeMicroseconds(ms);
}

//gets the current angle
int ServoMotor::GetPosition()
{
    return this->_curPos;
}
