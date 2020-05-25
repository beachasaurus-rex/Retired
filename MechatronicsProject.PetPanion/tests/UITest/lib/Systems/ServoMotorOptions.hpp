class ServoMotorOptions
{
    private:
        //servo's pin
        byte _pin;
    public:
        /*
        description: constructor
        inputs:
            1. pin number
        returns: instance of a servo motor options object
        */
        ServoMotorOptions(byte);
        /*
        description: gets the servo's pin number
        inputs: none
        returns: servo's pin number
        */
        byte GetPin(void);
};
