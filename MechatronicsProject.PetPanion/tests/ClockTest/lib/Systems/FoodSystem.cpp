#ifndef FOOD_SYSTEM_H
    #define FOOD_SYSTEM_H
    #include "FoodSystem.hpp"
#endif

//PRIVATE

void FoodSystem::OpenChute()
{
    this->_motor->Rotate(this->_degsOpen);
}

void FoodSystem::CloseChute()
{
    this->_motor->Rotate(this->_degsClose);
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

    this->_motor->Detach();
}

void FoodSystem::OperateServoLong
    (long val, void(FoodSystem::*func)(long))
{
    this->AttachServo();

    //call the function
    (this->*func)(val);

    this->_motor->Detach();
}

void FoodSystem::ActuateChute(long ms)
{
    this->OpenChute();
    delay(ms);
    this->CloseChute();
    delay(1000);
}

void FoodSystem::FoodDispensingAlgorithm()
{
    //store address to weight setpoint
    float* sp = &(this->_spWeight);
    //store address to acceptable error
    float* accErr = &(this->_err);
    //minimum delay possible for the servo motor
    long* minDelay = &(this->_minDelay);
    //initial guess for how long to hold the chute open
    long msOpenChute = this->_initDelay;

    //initially calibrate the servo
    this->ActuateChute(*minDelay);
    this->ActuateChute(*minDelay);

    //placeholder variables
    float weight = 0;
    float relErr = 0;
    boolean atSetpoint = 0;

    /*breaks when the actual weight is near the
    weight setpoint*/
    while (!atSetpoint)
    {
        //wait for food to stop moving
        delay(1000);

        //this must be negative to read a positive weight
        weight = fabs(this->_loadCell->Read());

        /*gets the absolute value of the relative error
        between the weight setpoint and the actual weight*/
        relErr = fabs(RelativeErr(*sp, weight));

        /*true if the relative error is between plus-minus
        the acceptable error*/
        atSetpoint =
            (relErr >= -(*accErr)) && (relErr <= *accErr);

        if (!atSetpoint)
        {
            /*if we exceed the range, then break out of the
            while loop. there's no way that we can put food
            back into the reservoir, so this is all we can do*/
            if (weight > ((*sp) + (*sp) * (*accErr)))
            {
                break;
            }

            /*assume that if we need x% more weight, then
            we need to reduce the time that the chute is open
            by that same percentage*/
            msOpenChute = msOpenChute * relErr;

            //absolute shortest time it can be open for
            if (msOpenChute < *minDelay)
            {
                msOpenChute = *minDelay;
            }

            //dispenses the food
            this->ActuateChute(msOpenChute);
        }
    }

    this->_weight = weight;
}

void FoodSystem::DebugFoodDispensingAlgorithm()
{
    //store address to weight setpoint
    float* sp = &(this->_spWeight);
    //store address to acceptable error
    float* accErr = &(this->_err);
    //minimum delay possible for the servo motor
    long* minDelay = &(this->_minDelay);
    //initial guess for how long to hold the chute open
    long msOpenChute = this->_initDelay;

    // initially calibrate the servo
    this->ActuateChute(*minDelay);
    this->ActuateChute(*minDelay);

    //placeholder variables
    float weight = 0;
    float relErr = 0;
    boolean atSetpoint = 0;

    /*breaks when the actual weight is near the
    weight setpoint*/
    while (!atSetpoint)
    {
        //wait for food to stop moving
        delay(1000);

        //this must be negative to read a positive weight
        weight = fabs(this->_loadCell->Read());

        Serial.print("Current weight: ");
        Serial.print(weight);
        Serial.println(" lbs");
        Serial.print("Weight Setpoint: ");
        Serial.print(*sp);
        Serial.println(" lbs");

        /*gets the absolute value of the relative error
        between the weight setpoint and the actual weight*/
        relErr = fabs(RelativeErr(*sp, weight));

        Serial.print("Relative error: ");
        Serial.println(relErr);

        /*true if the relative error is between plus-minus
        the acceptable error*/
        atSetpoint =
            (relErr >= -(*accErr)) && (relErr <= *accErr);

        if (!atSetpoint)
        {
            /*if we exceed the range, then break out of the
            while loop. there's no way that we can put food
            back into the reservoir, so this is all we can do*/
            if (weight > ((*sp) + (*sp) * (*accErr)))
            {
                break;
            }

            /*assume that if we need x% more weight, then
            we need to reduce the time that the chute is open
            by that same percentage*/
            msOpenChute = msOpenChute * relErr;

            //absolute shortest time it can be open for
            if (msOpenChute < *minDelay)
            {
                msOpenChute = *minDelay;
            }

            Serial.print("Chute open time: ");
            Serial.print(msOpenChute);
            Serial.println(" ms\n");

            //dispenses the food
            this->ActuateChute(msOpenChute);
        }
    }

    this->_weight = weight;
}

//PUBLIC

//constructor
FoodSystem::FoodSystem(int degsOpen, int degsClose, float weightSP,
    float err, long minDelay, long initDelay, LoadCellOptions* lcOpts,
    ServoMotorOptions* servOpts)
{
    this->_minDelay = minDelay;
    this->_initDelay = initDelay;
    this->_degsOpen = degsOpen;
    this->_degsClose = degsClose;
    this->_err = err;
    this->_spWeight = weightSP;

    this->_motor = new ServoMotor
        (
            servOpts->GetPin()
        );

    this->_loadCell = new LoadCell
        (
            lcOpts->GetDataOutputPin(),
            lcOpts->GetSerialClockPin(),
            lcOpts->GetGain(),
            lcOpts->GetCalibrationFactor()
        );
}

boolean FoodSystem::Setup(void)
{
    return this->_loadCell->Setup();
}

float FoodSystem::GetLastMeasuredWeight()
{
    return this->_weight;
}

void FoodSystem::DebugDispenseFood()
{
    FoodSystem::OperateServoVoid(&FoodSystem::DebugFoodDispensingAlgorithm);
}

void FoodSystem::DispenseFood()
{
    FoodSystem::OperateServoVoid(&FoodSystem::FoodDispensingAlgorithm);
}

void FoodSystem::ZeroScale()
{
    this->_loadCell->Zero();
}

void FoodSystem::OperateChute(long ms)
{
    FoodSystem::OperateServoLong(ms, &FoodSystem::ActuateChute);
}
