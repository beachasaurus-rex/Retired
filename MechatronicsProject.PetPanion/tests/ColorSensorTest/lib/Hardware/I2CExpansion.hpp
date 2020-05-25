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
        //constructor
        I2CExpansion(byte);
        /*
        selects the port on the expansion bus to
        communicate with.
        note: there are only ports 1 through 8.
        */
        void SelectPort(uint8_t);
        /*
        gets the actual hexadecimal address of the I2C expansion
        board
        */
        uint8_t* GetMainAddressHex(void);
        /*
        scans the ports of the I2C bus and prints the results
        to the serial monitor
        */
        void ScanPorts(void);
};
