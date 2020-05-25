class IRSensor
{
    private:
        byte _pin;
    public:
        /*
        description: constructor
        inputs: pin number
        returns: instance of an IR sensor object
        */
        IRSensor(byte);
        /*
        description: sets up the IR sensor
        inputs: none
        returns: true if setup is successful
        */
        boolean Setup(void);
        /*
        description: returns true if obstacle is found
        inputs: none
        returns: true if an obstacle is found
        */
        boolean FoundObstacle(void);
        byte GetPinNumber(void);
};
