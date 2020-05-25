#ifndef CLOCK_H
    #define CLOCK_H
    #include "Clock.hpp"
#endif

Clock::Clock(I2CExpansion* i2c, byte portId)
{
    this->_i2c = i2c;
    this->_rtc = new RTC();
    this->_portId = portId;
}

boolean Clock::Setup()
{
    this->_i2c->SelectPort(this->_portId);
    return this->_rtc->Setup();
}

void Clock::Adjust(DateTime val)
{
    this->_i2c->SelectPort(this->_portId);
    this->_rtc->Adjust(val);
}

DateTime Clock::Now()
{
    this->_i2c->SelectPort(this->_portId);
    return this->_rtc->Now();
}

boolean Clock::HasLostPower()
{
    this->_i2c->SelectPort(this->_portId);
    return this->_rtc->HasLostPower();
}

float Clock::GetTemperature()
{
    this->_i2c->SelectPort(this->_portId);
    return this->_rtc->GetTemperature();
}
