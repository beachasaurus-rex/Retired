#ifndef LOAD_CELL_H
    #define LOAD_CELL_H
    #include "LoadCell.hpp"
#endif

//constructor
LoadCell::LoadCell(byte outPin, byte sClockPin, byte gain,
    float calibrationFactor)
{
    this->_scale = new HX711();
    this->_outPin = outPin;
    this->_sClockPin = sClockPin;
    this->_gain = gain;
    this->_calFac = calibrationFactor;
    this->_isAsleep = true;
}

//sets up the load cell
boolean LoadCell::Setup()
{
    this->_scale->begin(this->_outPin, this->_sClockPin, this->_gain);
    this->_scale->set_scale(this->_calFac);
    this->_isAsleep = false;
    return true;
}

//zeros the load cell
void LoadCell::Zero()
{
    this->_scale->tare();
}

//puts the load cell into sleep mode
void LoadCell::Sleep()
{
    this->_scale->power_down();
    this->_isAsleep = true;
}

//wakes the load cell from sleep mode
void LoadCell::Awaken()
{
    if (this->_isAsleep)
    {
        this->_scale->power_up();
        this->_isAsleep = false;
    }
}

//reads from the load cell
float LoadCell::Read()
{
    if (!(this->_isAsleep))
    {
        return this->_scale->get_units();
    }
    else
    {
        this->Awaken();
        return this->_scale->get_units();
    }
}
