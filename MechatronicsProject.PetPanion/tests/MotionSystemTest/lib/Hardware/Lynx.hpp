#ifndef LYNX_MOTOR_H
    #define LYNX_MOTOR_H
    #include "LynxMotor.hpp"
#endif

class Lynx
{
    private:
        //motors on the left side of the lynx platform
        LynxMotor* _left;
        //motors on the right side of the lynx platform
        LynxMotor* _right;
    public:
        /*
        description: constructor
        inputs:
            1. pin number for the left motors
            2. pin number for the right motors
        returns: instance of a lynx object
        */
        Lynx(byte,byte);
        /*
        description: sets up the motors
        inputs: none
        returns: none
        */
        void Attach(void);
        /*
        description: kills power to the motors
        inputs: none
        returns: none
        */
        void Detach(void);
        /*
        description: returns true if all motors are attached
        inputs: none
        returns: true if all motors are attached
        */
        boolean AreAttached(void);
        /*
        description: continuously rotates the left motors
                     in tbe forward direction at the input speed
        inputs: speed value
        returns: none
        */
        void LeftForward(int);
        /*
        description: continuously rotates the left motors
                     in tbe backward direction at the input speed
        inputs: speed value
        returns: none
        */
        void LeftBackward(int);
        /*
        description: continuously rotates the right motors
                     in tbe forward direction at the input speed
        inputs: speed value
        returns: none
        */
        void RightForward(int);
        /*
        description: continuously rotates the right motors
                     in tbe backward direction at the input speed
        inputs: speed value
        returns: none
        */
        void RightBackward(int);
        /*
        description continuously moves the lynx platform forward at
                    the input speed
        inputs: speed value
        returns: none
        */
        void Forward(int);
        /*
        description: continuously moves the lynx platform backward at
                     the input speed
        inputs: speed value
        returns: none
        */
        void Backward(int);
        /*
        description: continuously moves the motors in their
                     forward directions at the input speeds
        inputs:
            1. speed value for the left motors
            2. speed value for the right motors
        returns: none
        */
        void TurnForward(int,int);
        /*
        description: continuously moves the motors in their
                     backward directions at the input speeds
        inputs:
            1. speed value for the left motors
            2. speed value for the right motors
        returns: none
        */
        void TurnBackward(int,int);
        /*
        description: stops all motors on the lynx platform
        inputs: none
        returns: none
        */
        void Stop(void);
};
