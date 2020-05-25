#ifndef LYNX_H
    #define LYNX_H
    #include "Lynx.hpp"
#endif

//constructor
Lynx::Lynx(byte leftPin, byte rightPin)
{
    this->_left =
        new LynxMotor(leftPin);
    this->_right =
        new LynxMotor(rightPin);
}

//sets up the motors
void Lynx::Attach()
{
    this->_left->Attach();
    this->_right->Attach();
}

//kills power to the motors
void Lynx::Detach()
{
    this->_left->Detach();
    this->_right->Detach();
}

//returns true if all motors are attached
boolean Lynx::AreAttached()
{
    return (this->_left->IsAttached()) &&
        (this->_right->IsAttached());
}

/*
continuously rotates the left motors
in tbe forward direction at the input speed
*/
void Lynx::LeftForward(int speed)
{
    this->_left->RotateForward(speed);
}

/*
continuously rotates the left motors
in tbe backward direction at the input speed
*/
void Lynx::LeftBackward(int speed)
{
    this->_left->RotateBackward(speed);
}

/*
continuously rotates the right motors
in tbe forward direction at the input speed
*/
void Lynx::RightForward(int speed)
{
    this->_right->RotateForward(speed);
}

/*
continuously rotates the right motors
in tbe backward direction at the input speed
*/
void Lynx::RightBackward(int speed)
{
    this->_right->RotateBackward(speed);
}

//continuously moves the lynx platform forward at the input speed
void Lynx::Forward(int speed)
{
    this->LeftForward(speed);
    this->RightForward(speed);
}

//continuously moves the lynx platform backward at the input speed
void Lynx::Backward(int speed)
{
    this->LeftBackward(speed);
    this->RightBackward(speed);
}

/*
continuously moves the motors in their
forward directions at the input speeds
*/
void Lynx::TurnForward(int leftSpeed, int rightSpeed)
{
    this->LeftForward(leftSpeed);
    this->RightForward(rightSpeed);
}

/*
continuously moves the motors in their
backward directions at the input speeds
*/
void Lynx::TurnBackward(int leftSpeed, int rightSpeed)
{
    this->LeftBackward(leftSpeed);
    this->RightBackward(rightSpeed);
}

//stops all motors on the lynx platform
void Lynx::Stop()
{
    this->_left->Stop();
    this->_right->Stop();
}
