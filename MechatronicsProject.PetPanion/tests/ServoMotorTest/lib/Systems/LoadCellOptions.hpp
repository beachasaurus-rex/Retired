class LoadCellOptions
{
    private:
        //data output pin
        byte _outPin;
        //serial clock pin
        byte _sClockPin;
        //gain
        byte _gain;
        //calibration factor
        float _calFac;
    public:
        /*
        description: constructor
        inputs:
            1. data output pin number
            2. serial clock pin number
            3. gain value
            4. calibration factor value
        returns: instance of a load cell options object
        */
        LoadCellOptions(byte,byte,byte,float);
        /*
        description: gets the data output pin number
        input: none
        returns: data output pin number
        */
        byte GetDataOutputPin(void);
        /*
        description: gets the serial clock pin number
        inputs: none
        returns: serial clock pin number
        */
        byte GetSerialClockPin(void);
        /*
        description: gets the gain value
        inputs: none
        returns: gain value
        */
        byte GetGain(void);
        /*
        description: gets the calibration factor
        inputs: none
        returns: calibration factor
        */
        float GetCalibrationFactor(void);
};
