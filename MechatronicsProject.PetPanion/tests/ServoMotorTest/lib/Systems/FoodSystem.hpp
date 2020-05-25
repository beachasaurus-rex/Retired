#ifndef DEPS_H
    #define DEPS_H
    #include "deps.hpp"
#endif

#ifndef LOAD_CELL_H
    #define LOAD_CELL_H
    #include "../Hardware/Sensors/LoadCell.hpp"
#endif
#ifndef LOAD_CELL_OPTIONS_H
    #define LOAD_CELL_OPTIONS_H
    #include "LoadCellOptions.hpp"
#endif

#ifndef SERVO_MOTOR_H
    #define SERVO_MOTOR_H
    #include "../Hardware/ServoMotor.hpp"
#endif
#ifndef SERVO_MOTOR_OPTIONS_H
    #define SERVO_MOTOR_OPTIONS_H
    #include "ServoMotorOptions.hpp"
#endif

#ifndef HELPERS_H
    #define HELPERS_H
    #include "../Helpers.hpp"
#endif

class FoodSystem
{
    private:
        //pointer to the servo motor
        ServoMotor* _motor;
        //pointer to the load cell
        LoadCell* _loadCell;
        //degrees to rotate the servo
        int _degs;
        //acceptable error tolerance
        float _err;
        //weight setpoint (units = lb)
        float _spWeight;
        //the current weight value (units = lb)
        float _curWeight;
        //the last measured weight value (units = lb)
        float _weight;
        /*
        description: wraps functions with no inputs or outputs
                     & correctly attaches the servo, while
                     detaching the servo after the input function pointer's
                     function has returned control to the caller
        inputs: function pointer to a function without inputs or outputs
        outputs: none
        */
        void OperateServoVoid(void(FoodSystem::*)(void));
        /*
        description: wraps functions with a long input and no outputs
                     & correctly attaches the servo, while
                     detaching the servo after the input function pointer's
                     function has returned control to the caller
        inputs:
            1. value to pass to the function pointer
            2. function pointer to a function with a long input & no ouputs
        outputs: none
        */
        void OperateServoLong(long, void(FoodSystem::*)(long));
        /*
        description: opens the food chute
        inputs: none
        returns: none
        */
        void OpenChute(void);
        /*
        description: closes the food chute
        inputs: none
        returns: none
        */
        void CloseChute(void);
        /*
        description: attaches the motor if it needs to be attached
                     and waits for the motor to be ready to operate
        inputs: none
        outputs: none
        */
        void AttachServo(void);
        /*
        description: opens the food chute for a given amount of
                     milliseconds and then closes it
        inputs: number of milliseconds to hold the chute open
        returns: none
        */
        void ActuateChute(long);
        /*
        description: attempts to dispense the amount of food equal to the
                     weight setpoint
        inputs: none
        returns: none
        */
        void DispenseFood(void);
    public:
        /*
        description: constructor
        inputs:
            1. degrees to rotate the servo
            2. weight setpoint in lb
            3. the acceptable error tolerance for the weight setpoint
            4. pointer to options for calibrating the load cell
            5. pointer to options for calibrating the servo motor
        returns: instance of a food system object

        dev notes:
            -Jon: I think that we should try to control how much food is let in
                  between each reading by varying how long we hold the food
                  chute open. This will allow us to reasonably say that we
                  created a control system by starting out with a large value
                  for the time to hold the chute open and then gradually reducing
                  it.

                  Before we even attempt this, we need to determine how quickly
                  the motor can reliably open and close.
        */
        FoodSystem(int,float,float,LoadCellOptions*,ServoMotorOptions*);
        /*
        description: returns the last measured weight value (units = lb)
        inputs: none
        returns: last measured weight value
        */
        float GetLastMeasuredWeight(void);
        /*
        description: awakens the servo motor -> calls ActuateChute ->
                     kills power to the servo motor
        inputs: number of milliseconds to hold the chute open
        returns: none
        */
        void OperateChute(long);
        /*
        description: awakens the servo motor -> calls DispenseFood ->
                     kills power to the servo motor
        inputs: none
        returns: none
        */
        void OperateFoodDispenser(void);
};
