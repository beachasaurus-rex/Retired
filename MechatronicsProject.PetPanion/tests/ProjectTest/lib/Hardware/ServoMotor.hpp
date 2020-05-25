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
    public:
        /*
        description: constructor
        inputs:
            1. pin number
        returns: instance of a servo motor object
        */
        ServoMotor(byte);
        /*
        description: sets up the motor
        inputs: none
        returns: none
        */
        void Attach(void);
        /*
        description: kills power to the motor
        inputs: none
        returns: none
        */
        void Detach(void);
        /*
        description: returns true if motor is attached
        inputs: none
        returns: true if motor is attached
        */
        boolean IsAttached(void);
        /*
        description: rotates the servo the input amount of degrees
        inputs: the number of degrees to rotate the motor
        returns: none
        */
        void Rotate(int);
        /*
        description sets the duration of each PWM pulse in microseconds
        inputs: the pulse with duration in microseconds
        returns: none
        */
        void SetPulseDuration(int);
};
