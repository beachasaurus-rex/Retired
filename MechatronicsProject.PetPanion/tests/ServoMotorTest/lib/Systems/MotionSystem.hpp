#ifndef DEPS_H
    #define DEPS_H
    #include "../deps.hpp"
#endif

#ifndef IR_SENSOR_H
    #define IR_SENSOR_H
    #include "../Hardware/Sensors/IRSensor.hpp"
#endif

#ifndef MOTION_SYSTEM_OPTIONS_H
    #define MOTION_SYSTEM_OPTIONS_H
    #include "MotionSystemOptions.hpp"
#endif

#ifndef LYNX_H
    #define LYNX_H
    #include "../Hardware/Lynx.hpp"
#endif

#ifndef COLOR_SENSOR_ARR_H
    #define COLOR_SENSOR_ARR_H
    #include "../Hardware/Sensors/ColorSensorArray.hpp"
#endif

#ifndef COLOR_SENSOR_ARR_OPTS_H
    #define COLOR_SENSOR_ARR_OPTS_H
    #include "../Hardware/Sensors/ColorSensorArrayOptions.hpp"
#endif

#ifndef I2C_EXP_H
    #define I2C_EXP_H
    #include "../Hardware/I2CExpansion.hpp"
#endif

#ifndef HELPERS_H
    #define HELPERS_H
    #include "../Helpers.hpp"
#endif

/*
At the time of writing:
    IR FRONT RANGE ~= 14in. = 35.5cm
    IR BACK RANGE ~= 24in. = 61cm
*/

/*required to determine when a stop ocurred due to
the IR sensor detecting an obstacle*/
volatile boolean _isCollisionStopped;

class MotionSystem
{
    private:
        //front IR sensor
        IRSensor* _irFront;
        //back IR sensor
        IRSensor* _irBack;
        //the color sensors
        ColorSensorArray* _csArr;
        //the motors
        Lynx* _lynx;
        //all other options for the entire system
        MotionSystemOptions* _msysOpts;
        /*
        description: starts the lynx motors -> calls the input function ->
                     kills power to the lynx motors
        inputs: function pointer that with no inputs or outputs
        returns: none
        */
        void OperateLynxMotors(void(MotionSystem::*)(void));
        /*
        description: moves the lynx platform forward
        inputs: none
        returns: none
        */
        void Forward(void);
        /*
        description: moves the lynx platform backward
        inputs: none
        returns: none
        */
        void Backward(void);
        /*
        description: turns the lynx platform left in the
                     foward direction
        inputs: none
        returns: none
        */
        void ForwardLeft(void);
        /*
        description: turns the lynx platform right in the
                     foward direction
        inputs: none
        returns: none
        */
        void ForwardRight(void);
        /*
        description: turns the lynx platform left in the
                     backward direction
        inputs: none
        returns: none
        */
        void BackwardLeft(void);
        /*
        description: turns the lynx platform right in the
                     backward direction
        inputs: none
        returns: none
        */
        void BackwardRight(void);
        /*
        description: algorithm that allows the lynx platform to travel
                     to a destination
        inputs:
            1. function pointer to function for straight movement
            2. function pointer to function for turning left
            3. function pointer to function for turning right
        returns: none
        */
        void PathingAlgorithm(void(MotionSystem::*)(void),
                              void(MotionSystem::*)(void),
                              void(MotionSystem::*)(void));
        /*
        description: same as pathing algorithm except it makes the
                     arduino report things to the serial console
                     for debugging purposes
        inputs:
            1. function pointer to function for straight movement
            2. function pointer to function for turning left
            3. function pointer to function for turning right
        returns: none
        */
        void DebugPathingAlgorithm(void(MotionSystem::*)(void),
                                   void(MotionSystem::*)(void),
                                   void(MotionSystem::*)(void));
        /*
        description: follows path in the forward direction
        inputs: none
        returns: none
        */
        void ForwardPathing(void);
        /*
        description: follows path in the backward direction
        inputs: none
        returns: none
        */
        void BackwardPathing(void);
        /*
        description: same as ForwardPathing except that it uses the
                     debugging algorithm
        inputs: none
        returns: none
        */
        void DebugForwardPathing(void);
        /*
        description: same as BackwardPathing except that it uses the
                     debugging algorithm
        inputs: none
        returns: none
        */
        void DebugBackwardPathing(void);
    public:
        /*
        description: constructor
        inputs:
            1. pin number for the left motors
            2. pin number for the right motors
            3. pointer to options for the motion system
            4. pointer to I2C expansion bus
            5. options for the color sensor array
            6. pointer to the IR sensor in the front
            7. pointer to the IR sensor in the back
        outputs: instance of a lynx platform object
        */
        MotionSystem(byte, byte, MotionSystemOptions*,I2CExpansion*,
                ColorSensorArrayOptions,IRSensor*,IRSensor*);
        /*
        description: sets the system up
        inputs: none
        returns: true when ready
        */
        boolean Setup(void);
        /*
        description: activates motors -> calls ForwardPathing -> kills power
                     to the motors
        inputs: none
        outputs: none
        */
        void GoHome(void);
        /*
        description: activates motors -> calls BackwardPathing ->
                     kills power to the motors
        inputs: none
        outputs: none
        */
        void GotoFeedingLocation(void);
        /*
        description: same as GoHome except that it uses the
                     debugging algorithm
        inputs: none
        outputs: none
        */
        void DebugGoHome(void);
        /*
        description: same as GotoFeedingLocation except that it uses the
                     debugging algorithm
        inputs: none
        outputs: none
        */
        void DebugGotoFeedingLocation(void);
        /*
        description: forces the platform to stop moving under
                     any circumstance
        input: none
        outputs: none
        note: use this for the interrupt pins
        */
        void CollisionStop(void);
        /*
        description: turns on all color sensor LEDs
        inputs: none
        returns: none
        */
        void ActivateLeds(void);
        /*
        description: turns off all color sensor LEDs
        inputs: none
        returns: none
        */
        void DeactivateLeds(void);
        /*
        description: gets a pointer to the IR sensor in the front
        inputs: none
        returns: pointer to the IR sensor in the front
        */
        IRSensor* GetFrontIRSensor(void);
        /*
        description: gets a pointer to the IR sensor in the back
        inputs: none
        returns: pointer to the IR sensor in the back
        */
        IRSensor* GetBackIRSensor(void);
};
