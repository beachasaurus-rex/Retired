class IRSensor
{
    private:
        byte _pin;
    public:
        //constructor
        IRSensor(byte);
        //sets up the IR sensor
        boolean Setup(void);
        //returns true if obstacle is found
        boolean FoundObstacle(void);
};
