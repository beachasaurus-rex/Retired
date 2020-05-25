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

        /*
        description: constructor
        inputs:
            1. integration time setting
            2. gain setting
            3. led pin number
        returns: instance of ColorSensor object

        note: IntegrationTime & Gain can be found in Enums.hpp.
        */
        ColorSensor(IntegrationTime, Gain, byte);
        /*
        description: sets up the sensor
        inputs: none
        returns: true if setup is successful
        */
        boolean Setup(void);
        /*
        description: enables the sensor
        inputs: none
        returns: none
        */
        void Enable(void);
        /*
        description: disables the sensor
        inputs: none
        returns: none
        */
        void Disable(void);
        /*
        description: removes any interrupts from the sensor
        inputs: none
        returns: none
        */
        void ClearInterrupts(void);
        /*
        description: returns an array of RGB values
        inputs: none
        returns: an array of RGB values:
            index 0 = red
            index 1 = green
            index 2 = blue
        */
        float* GetRGB(void);
        /*
        description: returns the color temperature
        inputs: array of RGB values
        returns: color temperature value
        */
        uint16_t GetColorTemperature(float*);
        /*
        description: returns the lux (brightness)
        inputs: array of RGB values
        returns: lux value
        */
        uint16_t GetLux(float*);
        /*
        description: sets the pin for the led
        inputs: led pin number
        returns: none
        */
        void SetLedPin(byte);
        /*
        description: gets the current setting for gain
        inputs: none
        returns: gain setting value
        */
        tcs34725Gain_t* GetGain(void);
        /*
        description: sets the gain setting
        inputs: gain setting
        returns: none
        */
        void SetGain(Gain);
        /*
        description: gets the current setting for the integral time
        inputs: none
        returns: integration time setting value
        */
        tcs34725IntegrationTime_t* GetIntegrationTime(void);
        /*
        description: sets the integral time
        inputs: integration time setting
        returns: none
        */
        void SetIntegrationTime(IntegrationTime);
        /*
        description: turns the LED on
        inputs: none
        returns: none
        */
        void LedOn(void);
        /*
        description: turns the LED off
        inputs: none
        returns: none
        */
        void LedOff(void);
};
