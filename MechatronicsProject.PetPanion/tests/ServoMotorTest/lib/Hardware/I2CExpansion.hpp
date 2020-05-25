#ifndef DEPS_H
    #define DEPS_H
    #include "../deps.hpp"
#endif

/*
note: Assumes Wire.begin() has already been called.
*/
class I2CExpansion
{
    private:
        uint8_t _mainAddr;
        byte _mainPort;
    public:
        /*
        description: constructor
        inputs: the pin number for the main port
        returns: an instance of an I2C expansion bus object
        */
        I2CExpansion(byte);
        /*
        description: selects the port on the expansion bus to
                     communicate with.
        inputs: port number
        returns: none
        note: there are only ports 1 through 8.
        */
        void SelectPort(uint8_t);
        /*
        description: gets the actual hexadecimal address of the
                     I2C expansion board
        inputs: none
        returns: hexadecimal address of the I2C expansion bus
        */
        uint8_t* GetMainAddressHex(void);
        /*
        description: scans the ports of the I2C bus and prints the
                     results to the serial monitor
        inputs: none
        returns: none
        */
        void ScanPorts(void);
};
