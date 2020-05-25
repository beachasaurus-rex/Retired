#ifndef DEPS_H
    #define DEPS_H
    #include "../../deps.hpp"
#endif

class LoadCell
{
    private:
        //pointer to load cell base
        HX711* _scale;
        //output pin
        byte _outPin;
        //serial clock pin
        byte _sClockPin;
        //gain
        byte _gain;
        //calibration factor
        float _calFac;
        boolean _isAsleep;
    public:
        //constructor
        LoadCell(byte,byte,byte,float);
        //sets up the load cell
        boolean Setup(void);
        //reads from the load cell
        float Read(void);
        //zeros the load cell
        void Zero(void);
        //puts the load cell into sleep mode
        void Sleep(void);
        //wakes the load cell from sleep mode
        void Awaken(void);
};
