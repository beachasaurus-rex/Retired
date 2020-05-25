#ifndef MOTION_SYSTEM_OPTIONS_H
    #define MOTION_SYSTEM_OPTIONS_H
    #include "MotionSystemOptions.hpp"
#endif

MotionSystemOptions::MotionSystemOptions(float csHigh, float csLow,
    int spd, int turnSlowSpeed, int turnFastSpeed)
{
    this->_csHigh = csHigh;
    this->_csLow = csLow;
    this->_spd = spd;
    this->_turnSlowSpeed = turnSlowSpeed;
    this->_turnFastSpeed = turnFastSpeed;
}

int MotionSystemOptions::GetSpeed(void)
{
    return this->_spd;
}

int MotionSystemOptions::GetSlowTurningSpeed(void)
{
    return this->_turnSlowSpeed;
}

int MotionSystemOptions::GetFastTurningSpeed(void)
{
    return this->_turnFastSpeed;
}

float MotionSystemOptions::GetHighColorSensorValue(void)
{
    return this->_csHigh;
}

float MotionSystemOptions::GetLowColorSensorValue(void)
{
    return this->_csLow;
}
