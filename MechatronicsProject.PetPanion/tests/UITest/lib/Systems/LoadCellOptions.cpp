#ifndef LOAD_CELL_OPTIONS_H
    #define LOAD_CELL_OPTIONS_H
    #include "LoadCellOptions.hpp"
#endif

//constructor
 LoadCellOptions::LoadCellOptions(byte dOutPin, byte sClockPin,
    byte gain, float calibrationFactor)
 {
     this->_outPin = dOutPin;
     this->_sClockPin = sClockPin;
     this->_gain = gain;
     this->_calFac = calibrationFactor;
 }

//gets the data output pin number
byte LoadCellOptions::GetDataOutputPin()
{
    return this->_outPin;
}

//gets the serial clock pin number
byte LoadCellOptions::GetSerialClockPin()
{
    return this->_sClockPin;
}

//gets the gain value
byte LoadCellOptions::GetGain()
{
    return this->_gain;
}

//gets the calibration factor
float LoadCellOptions:: GetCalibrationFactor()
{
    return this->_calFac;
}
