#ifndef DEPS_H
    #define DEPS_H
    #include "../../deps.hpp"
#endif

class LoadCell
{
    private:
        //pointer to load cell base
        HX711* _scale;
        //data output pin
        byte _outPin;
        //serial clock pin
        byte _sClockPin;
        //gain
        byte _gain;
        //calibration factor
        float _calFac;
        boolean _isAsleep;
    public:
        /*
        description: constructor
        inputs:
            1. data output pin number
            2. serial clock pin number
            3. gain value
            4. calibration factor value
        returns: instance of a load cell object
        */
        LoadCell(byte,byte,byte,float);
        /*
        description: sets up the load cell
        inputs: none
        returns: true if setup is successful
        */
        boolean Setup(void);
        /*
        description: reads from the load cell
        inputs: none
        returns: load cell reading value
        */
        float Read(void);
        /*
        description: zeros the load cell
        inputs: none
        returns: none
        */
        void Zero(void);
        /*
        description: puts the load cell into sleep mode
        inputs: none
        returns: none
        */
        void Sleep(void);
        /*
        description: wakes the load cell from sleep mode
        inputs: none
        returns: none
        */
        void Awaken(void);
};
