class MotionSystemOptions
{
private:
    //forward & backward speed
    int _spd;
    //speed of the slowest motor while turning
    int _turnSlowSpeed;
    //speed of the fastest motor while turning
    int _turnFastSpeed;
    //"high" value for color sensors
    float _csHigh;
    //"low" value for color sensors
    float _csLow;
public:
    /*
    description: constructor
    inputs:
        1. "high" value for color sensors
        2. "low" value for color sensors
        3. motor speed for going straight
        4. slowest motor turning speed
        5. fastest motor turning speed
    returns: instance of a motion systems options object
    */
    MotionSystemOptions(float,float,int,int,int);
    int GetSpeed(void);
    int GetSlowTurningSpeed(void);
    int GetFastTurningSpeed(void);
    float GetHighColorSensorValue(void);
    float GetLowColorSensorValue(void);
};
