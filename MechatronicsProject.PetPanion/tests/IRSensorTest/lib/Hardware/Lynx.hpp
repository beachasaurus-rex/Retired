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
        //constructor
        Lynx(byte,byte);
        //sets up the motors
        void Attach(void);
        //kills power to the motors
        void Detach(void);
        //returns true if all motors are attached
        boolean AreAttached(void);
        /*
        continuously rotates the left motors
        in tbe forward direction at the input speed
        */
        void LeftForward(int);
        /*
        continuously rotates the left motors
        in tbe backward direction at the input speed
        */
        void LeftBackward(int);
        /*
        continuously rotates the right motors
        in tbe forward direction at the input speed
        */
        void RightForward(int);
        /*
        continuously rotates the right motors
        in tbe backward direction at the input speed
        */
        void RightBackward(int);
        //continuously moves the lynx platform forward at the input speed
        void Forward(int);
        //continuously moves the lynx platform backward at the input speed
        void Backward(int);
        /*
        continuously moves the motors in their
        forward directions at the input speeds
        */
        void TurnForward(int,int);
        /*
        continuously moves the motors in their
        backward directions at the input speeds
        */
        void TurnBackward(int,int);
        //stops all motors on the lynx platform
        void Stop(void);
};
