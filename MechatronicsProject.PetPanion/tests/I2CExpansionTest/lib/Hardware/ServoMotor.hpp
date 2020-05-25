#ifndef DEPS_H
    #define DEPS_H
    #include "../deps.hpp"
#endif

/*
This class is intended to be a thin wrapper around the
built-in Servo.h library.
*/
class ServoMotor
{
    private:
        //servo base
        Servo* _motor;
        //servo's pin
        byte _pin;
        //minimum rotation in degrees
        int _minRot;
        //maximum rotation in degrees
        int _maxRot;
        //current angle of the servo
        int _curPos;
    public:
        //constructor
        ServoMotor(byte,int,int);
        //sets up the motor
        void Attach(void);
        //kills power to the motor
        void Detach(void);
        //returns true if motor is attached
        boolean IsAttached(void);
        //rotates the servo the input amount of degrees
        void Rotate(int);
        //sets the duration of each PWM pulse in microseconds
        void SetPulseDuration(int);
        //gets the current angle
        int GetPosition(void);
};
