#ifndef ENUMS_H
    #define ENUMS_H
    #include "../../Enums.hpp"
#endif

#ifndef DEPS_H
    #define DEPS_H
    #include "../../deps.hpp"
#endif

/*
Definition of a color sensor. This is intended to wrap around
the TCS34725 class provided by Adafruit.
*/
class ColorSensor
{
    private:
        //the actual sensor we're wrapping around
        Adafruit_TCS34725* _sen;
        //current integration time
        tcs34725IntegrationTime_t _intTime;
        //current gain
        tcs34725Gain_t _gain;
        //led pin #
        byte _ledPin;
    public:
        //constructor
        ColorSensor(IntegrationTime, Gain, byte);
        //sets up the sensor
        boolean Setup(void);
        //enables the sensor
        void Enable(void);
        //disables the sensor
        void Disable(void);
        //removes any interrupts from the sensor
        void ClearInterrupts(void);
        //returns an array of RGB values
        float* GetRGB(void);
        //returns the color temperature
        uint16_t GetColorTemperature(float*);
        //returns the lux (brightness)
        uint16_t GetLux(float*);
        //sets the pin for the led
        void SetLedPin(byte);
        //gets the current setting for gain
        tcs34725Gain_t* GetGain(void);
        //sets the gain setting
        void SetGain(Gain);
        //gets the current setting for the integral time
        tcs34725IntegrationTime_t* GetIntegrationTime(void);
        //sets the integral time
        void SetIntegrationTime(IntegrationTime);
        //turns the LED on
        void LedOn(void);
        //turns the LED off
        void LedOff(void);
};
