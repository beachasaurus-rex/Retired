#ifndef FOOD_SYSTEM_H
    #define FOOD_SYSTEM_H
    #include "FoodSystem.hpp"
#endif

//PRIVATE

void FoodSystem::OpenChute()
{
    this->_motor->Rotate(this->_degs);
}

void FoodSystem::CloseChute()
{
    this->_motor->Rotate(-(this->_degs));
}

void FoodSystem::AttachServo()
{
    /*checks if the motor is attached. if it's not attached
    then attach it and wait for hardware to register that
    the motor is attached.*/
    if (!(this->_motor->IsAttached()))
    {
        this->_motor->Attach();

        //waits until the motor is attached
        while(!(this->_motor->IsAttached()));
    }
}

void FoodSystem::OperateServoVoid(void(FoodSystem::*func)(void))
{
    this->AttachServo();

    //call the function
    (this->*func)();

    delay(250);
    this->_motor->Detach();
}

void FoodSystem::OperateServoLong
    (long val, void(FoodSystem::*func)(long))
{
    this->AttachServo();

    //call the function
    (this->*func)(val);

    delay(250);
    this->_motor->Detach();
}

void FoodSystem::ActuateChute(long ms)
{
    this->OpenChute();
    delay(ms);
    this->CloseChute();
}

void FoodSystem::DispenseFood()
{
    //store address to weight setpoint
    float* sp = &(this->_spWeight);
    //store address to acceptable error
    float* accErr = &(this->_err);

    //initial guess for how long to hold the chute open
    long msOpenChute = 500;

    //placeholder variables
    float weight = 0;
    float relErr = 0;
    boolean atSetpoint = 0;

    /*breaks when the actual weight is near the
    weight setpoint*/
    while (!atSetpoint)
    {
        weight = this->_loadCell->Read();

        /*gets the absolute value of the relative error
        between the weight setpoint and the actual weight*/
        relErr = fabs(RelativeErr(*sp, weight));

        /*true if the relative error is between plus-minus
        the acceptable error*/
        atSetpoint =
            (relErr >= -(*accErr)) && (relErr <= *accErr);

        if (!atSetpoint)
        {
            /*if we exceed the setpoint, then break out of the
            while loop. there's no way that we can put food
            back into the reservoir, so this is all we can do*/
            float err = *sp - weight;
            if (err / err == -1)
            {
                break;
            }

            /*assume that if we need x% more weight, then
            we need to reduce the time that the chute is open
            by that same percentage*/
            msOpenChute = msOpenChute * relErr;

            //dispenses the food
            this->ActuateChute(msOpenChute);
        }
    }

    this->_weight = weight;
}

//PUBLIC

//constructor
FoodSystem::FoodSystem(int degs, float weightSP, float err,
    LoadCellOptions* lcOpts, ServoMotorOptions* servOpts)
{
    this->_degs = degs;
    this->_err = err;
    this->_spWeight = weightSP;

    this->_motor = new ServoMotor
        (
            servOpts->GetPin(),
            servOpts->GetMinRotation(),
            servOpts->GetMaxRotation()
        );

    this->_loadCell = new LoadCell
        (
            lcOpts->GetDataOutputPin(),
            lcOpts->GetSerialClockPin(),
            lcOpts->GetGain(),
            lcOpts->GetCalibrationFactor()
        );
}

float FoodSystem::GetLastMeasuredWeight()
{
    return this->_weight;
}

void FoodSystem::OperateChute(long ms)
{
    FoodSystem::OperateServoLong(ms, &FoodSystem::ActuateChute);
}

void FoodSystem::OperateFoodDispenser()
{
    FoodSystem::OperateServoVoid(&FoodSystem::DispenseFood);
}
