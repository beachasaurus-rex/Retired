#ifndef DEPS_H
    #define DEPS_H
    #include "../deps.hpp"
#endif

/*
This class is intended to be a thin wrapper around the
built-in Servo.h library.
*/
class LynxMotor
{
    private:
        //servo base
        Servo* _motor;
        //servo's pin
        byte _pin;
        //the stopping speed
        int _stop;
    public:
        //constructor
        LynxMotor(byte);
        //sets up the motor
        void Attach(void);
        //kills power to the motor
        void Detach(void);
        //stops the motor from rotating
        void Stop(void);
        //returns true if all motors are attached
        boolean AreAttached(void);
        //returns true if motor is attached
        boolean IsAttached(void);
        //rotates the lynx motor forward at the specified speed
        void RotateForward(int);
        //rotates the lynx motor backward at the specified speed
        void RotateBackward(int);
        //sets the duration of each PWM pulse in microseconds
        void SetPulseDuration(int);
};
