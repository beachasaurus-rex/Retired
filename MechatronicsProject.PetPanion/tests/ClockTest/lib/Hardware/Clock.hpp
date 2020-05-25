#ifndef RTC_H
    #define RTC_H
    #include "Hardware/Sensors/RTC.hpp"
#endif

#ifndef I2C_EXP_H
    #define I2C_EXP_H
    #include "Hardware/I2CExpansion.hpp"
#endif

class Clock
{
    private:
        //pointer to i2c bus
        I2CExpansion* _i2c;
        //pointer to real time clock
        RTC* _rtc;
        //i2c bus port id
        byte _portId;
    public:
        /*
        description: constructor
        inputs:
            1. i2c expansion bus pointer
            2. connection port # into the i2c bus
        returns: instance of a clock object that communicates through
                 the i2c port
        */
        Clock(I2CExpansion*,byte);
        /*
        description: sets up the RTC
        inputs: none
        returns: true if setup is successful
        */
        boolean Setup(void);
        void Adjust(DateTime);
        DateTime Now(void);
        boolean HasLostPower(void);
        float GetTemperature(void);
};
