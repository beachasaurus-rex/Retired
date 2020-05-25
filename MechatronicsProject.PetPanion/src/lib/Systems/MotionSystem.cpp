#ifndef MOTION_SYSTEM_H
    #define MOTION_SYSTEM_H
    #include "MotionSystem.hpp"
#endif

//EXPOSED STATIC FUNCTIONS
void InterruptStop()
{
    _isCollisionStopped = true;
}

//PRIVATE

/*starts the lynx motors -> calls the input function ->
kills power to the lynx motors*/
void MotionSystem::OperateLynxMotors
    (void(MotionSystem::*func)(void))
{
    this->_csArr->ActivateLeds();
    this->_lynx->Attach();

    (this->*func)();

    this->_csArr->DeactivateLeds();
    this->_lynx->Stop();
    delay(150);
    this->_lynx->Detach();
}

//moves the lynx platform forward
void MotionSystem::Forward()
{
    this->_lynx->Forward(this->_msysOpts->GetSpeed());
}

//moves the lynx platform backward
void MotionSystem::Backward()
{
    this->_lynx->Backward(this->_msysOpts->GetSpeed());
}

/*turns the lynx platform left in the
foward direction*/
void MotionSystem::ForwardLeft()
{
    int leftSpeed = this->_msysOpts->GetSlowTurningSpeed();
    int rightSpeed = this->_msysOpts->GetFastTurningSpeed();

    this->_lynx->TurnForward(leftSpeed, rightSpeed);
}

/*turns the lynx platform right in the
foward direction*/
void MotionSystem::ForwardRight()
{
    int leftSpeed = this->_msysOpts->GetFastTurningSpeed();
    int rightSpeed = this->_msysOpts->GetSlowTurningSpeed();

    this->_lynx->TurnForward(leftSpeed, rightSpeed);
}

/*turns the lynx platform left in the
backward direction*/
void MotionSystem::BackwardLeft()
{
    int leftSpeed = this->_msysOpts->GetFastTurningSpeed();
    int rightSpeed = this->_msysOpts->GetSlowTurningSpeed();

    this->_lynx->TurnBackward(leftSpeed, rightSpeed);
}

/*turns the lynx platform right in the
backward direction*/
void MotionSystem::BackwardRight()
{
    int leftSpeed = this->_msysOpts->GetSlowTurningSpeed();
    int rightSpeed = this->_msysOpts->GetFastTurningSpeed();

    this->_lynx->TurnBackward(leftSpeed, rightSpeed);
}

/*algorithm that allows the lynx platform to travel
to a destination*/
void MotionSystem::PathingAlgorithm(
    void(MotionSystem::*straight)(void),
    void(MotionSystem::*left)(void),
    void(MotionSystem::*right)(void))
{
    float high = this->_msysOpts->GetHighColorSensorValue();
    float low = this->_msysOpts->GetLowColorSensorValue();
    float** rgbVals = 0;
    float* redLeft = 0;
    float* redRight = 0;
    float* redMid = 0;
    boolean leftStrongest = false;
    boolean rightStrongest = false;
    boolean midStrongest = false;
    boolean isAtDestination = false;
    boolean allAreHigh = false;
    boolean allAreLow = false;

    (this->*straight)();
    delay(750);

    while (1)
    {
        if (_isCollisionStopped)
        {
            this->_lynx->Stop();
            _isCollisionStopped = false;
            break;
        }

        rgbVals = this->_csArr->ReadRGBValues();

        redLeft = &(rgbVals[0][0]);
        redMid = &(rgbVals[1][0]);
        redRight = &(rgbVals[2][0]);

        leftStrongest = (*redLeft > *redRight) &&
                        (*redLeft > *redMid);
        midStrongest = (*redMid > *redLeft) &&
                       (*redMid > *redRight);
        rightStrongest = (*redRight > *redLeft) &&
                         (*redRight > *redMid);
        allAreHigh = (*redLeft >= high) &&
                     (*redMid >= high) &&
                     (*redRight >= high);
        allAreLow = (*redLeft <= low) &&
                    (*redMid <= low) &&
                    (*redRight <= low);

        if (allAreHigh)
        {
            break;
        }
        else if (midStrongest || allAreLow)
        {
            (this->*straight)();
        }
        else if (leftStrongest)
        {
            (this->*left)();
        }
        else if (rightStrongest)
        {
            (this->*right)();
        }
    }
}

void MotionSystem::DebugPathingAlgorithm(
    void(MotionSystem::*straight)(void),
    void(MotionSystem::*left)(void),
    void(MotionSystem::*right)(void))
{
    Serial.println("Servos attached.");

    float high = this->_msysOpts->GetHighColorSensorValue();
    float low = this->_msysOpts->GetLowColorSensorValue();
    float** rgbVals = 0;
    float* redLeft = 0;
    float* redRight = 0;
    float* redMid = 0;
    boolean leftStrongest = false;
    boolean rightStrongest = false;
    boolean midStrongest = false;
    boolean isAtDestination = false;
    boolean allAreHigh = false;
    boolean allAreLow = false;
    while (1)
    {
        if (_isCollisionStopped)
        {
            Serial.println("Sensed obstacle -> preparing to stop.");
            this->_lynx->Stop();
            _isCollisionStopped = false;
            break;
        }

        rgbVals = this->_csArr->ReadRGBValues();

        redLeft = &(rgbVals[0][0]);
        redMid = &(rgbVals[1][0]);
        redRight = &(rgbVals[2][0]);

        Serial.print("R1: ");
        Serial.print(*redLeft);
        Serial.print(" R2: ");
        Serial.print(*redMid);
        Serial.print(" R3: ");
        Serial.print(*redRight);
        Serial.print("\n");

        leftStrongest = (*redLeft > *redRight) &&
                        (*redLeft > *redMid);
        midStrongest = (*redMid > *redLeft) &&
                       (*redMid > *redRight);
        rightStrongest = (*redRight > *redLeft) &&
                         (*redRight > *redMid);
        allAreHigh = (*redLeft >= high) &&
                     (*redMid >= high) &&
                     (*redRight >= high);
        allAreLow = (*redLeft <= low) &&
                    (*redMid <= low) &&
                    (*redRight <= low);

        if (allAreHigh)
        {
            Serial.println("Preparing to stop & detach servos.");
            break;
        }
        else if (midStrongest || allAreLow)
        {
            (this->*straight)();
        }
        else if (leftStrongest)
        {
            (this->*left)();
        }
        else if (rightStrongest)
        {
            (this->*right)();
        }
    }
}

//follows path in the forward direction
void MotionSystem::ForwardPathing()
{
    this->PathingAlgorithm
        (
            &MotionSystem::Forward,
            &MotionSystem::ForwardLeft,
            &MotionSystem::ForwardRight
        );
}

//follows path in the backward direction
void MotionSystem::BackwardPathing()
{
    this->PathingAlgorithm
        (
            &MotionSystem::Backward,
            &MotionSystem::BackwardLeft,
            &MotionSystem::BackwardRight
        );
}

/*same as ForwardPathing except that it uses the
debugging algorithm*/
void MotionSystem::DebugForwardPathing()
{
    this->DebugPathingAlgorithm
        (
            &MotionSystem::Forward,
            &MotionSystem::ForwardLeft,
            &MotionSystem::ForwardRight
        );
}

/*same as BackwardPathing except that it uses the
debugging algorithm*/
void MotionSystem::DebugBackwardPathing()
{
    this->DebugPathingAlgorithm
        (
            &MotionSystem::Backward,
            &MotionSystem::BackwardLeft,
            &MotionSystem::BackwardRight
        );
}

//PUBLIC

//description: constructor
MotionSystem::MotionSystem(byte leftPin, byte rightPin,
    MotionSystemOptions* msysOpts, I2CExpansion* i2cExp,
    ColorSensorArrayOptions csaOpts, IRSensor* irFront,
    IRSensor* irBack)
{
    this->_msysOpts = msysOpts;
    this->_lynx = new Lynx(leftPin, rightPin);
    this->_csArr = new ColorSensorArray(i2cExp, csaOpts);
    this->_irFront = irFront;
    this->_irBack = irBack;
}

//sets the system up
boolean MotionSystem::Setup()
{
    this->_irFront->Setup();
    this->_irBack->Setup();
    attachInterrupt(digitalPinToInterrupt(this->_irFront->GetPinNumber()),
            InterruptStop, FALLING);
    attachInterrupt(digitalPinToInterrupt(this->_irBack->GetPinNumber()),
        InterruptStop, FALLING);
    return this->_csArr->Setup();
}

/*activates motors -> calls ForwardPathing -> kills power
to the motors*/
void MotionSystem::GoHome()
{
    this->OperateLynxMotors(&MotionSystem::ForwardPathing);
}

/*activates motors -> calls BackwardPathing ->
kills power to the motors*/
void MotionSystem::GotoFeedingLocation()
{
    this->
        OperateLynxMotors(&MotionSystem::BackwardPathing);
}

/*forces the platform to stop moving under
any circumstance*/
void MotionSystem::CollisionStop()
{
    this->_lynx->Stop();
}

/*same as GoHome except that it uses the
debugging algorithm*/
void MotionSystem::DebugGoHome()
{
    this->OperateLynxMotors(&MotionSystem::DebugForwardPathing);
}

/*same as GotoFeedingLocation except that it uses the
debugging algorithm*/
void MotionSystem::DebugGotoFeedingLocation()
{
    this->
        OperateLynxMotors(&MotionSystem::DebugBackwardPathing);
}

//turns on all color sensor LEDs
void MotionSystem::ActivateLeds()
{
    this->_csArr->ActivateLeds();
}

//turns off all color sensor LEDs
void MotionSystem::DeactivateLeds()
{
    this->_csArr->DeactivateLeds();
}
