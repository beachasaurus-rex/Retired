class ServoMotorOptions
{
    private:
        //servo's pin
        byte _pin;
        //minimum rotation in degrees
        int _minRot;
        //maximum rotation in degrees
        int _maxRot;
    public:
        /*
        description: constructor
        inputs:
            1. pin number
            2. minimum rotation
            3. maximum rotation
        returns: instance of a servo motor options object
        */
        ServoMotorOptions(byte,int,int);
        /*
        description: gets the servo's pin number
        inputs: none
        returns: servo's pin number
        */
        byte GetPin(void);
        /*
        description: gets the servo's minimum rotation
        inputs: none
        returns: servo's minimum rotation
        */
        int GetMinRotation(void);
        /*
        description: gets the servo's maximum rotation
        inputs: none
        returns: servo's maximum rotation
        */
        int GetMaxRotation(void);
};
