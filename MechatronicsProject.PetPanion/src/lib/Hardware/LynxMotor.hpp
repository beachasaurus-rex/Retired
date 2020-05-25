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
        /*
        description: constructor
        inputs: pin number for the motor
        returns: instance of a lynx motor object
        */
        LynxMotor(byte);
        /*
        description: sets up the motor
        inputs: none
        returns: none
        */
        void Attach(void);
        /*
        description: kills power to the motor
        inptus: none
        returns: none
        */
        void Detach(void);
        /*
        description: stops the motor from rotating
        inputs: none
        returns: none
        */
        void Stop(void);
        /*
        description: returns true if the motor is attached
        inputs: none
        returns: true if the motor is attached
        */
        boolean IsAttached(void);
        /*
        description: rotates the lynx motor forward at the specified speed
        inputs: speed value
        returns: none
        */
        void RotateForward(int);
        /*
        description: rotates the lynx motor backward at the specified speed
        inputs: speed value
        returns: none
        */
        void RotateBackward(int);
        /*
        description: sets the duration of each PWM pulse in microseconds
        inputs: pulse width duration in microseconds
        returns: none
        */
        void SetPulseDuration(int);
};
