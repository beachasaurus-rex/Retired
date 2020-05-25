#ifndef WIRE_H
    #define WIRE_H
    #include <Wire.h>
#endif

#ifndef I2C_EXP_H
    #define I2C_EXP_H
    #include "I2CExpansion.hpp"
#endif

#ifndef I2C_SCAN_UTILITY_H
    #define I2C_SCAN_UTILITY_H
    extern "C"
    {
      #include "utility/twi.h"
    }
#endif

//constructor
I2CExpansion::I2CExpansion(byte mainPort)
{
    if (mainPort > 0 && mainPort < 9)
    {
        _mainAddr = 0x70 + (mainPort - 1);
    }
    else
    {
        /*
        can't throw errors in this environment, so set this
        to the default otherwise
        */
        _mainAddr = 0x70;
    }
}

/*
selects the port on the expansion bus to
communicate with.
note: there are only ports 0 through 7.
*/
void I2CExpansion::SelectPort(uint8_t portNumber)
{
    if (portNumber < 0 || portNumber > 7)
    {
        Serial.print("Bad port number: ");
        Serial.println(portNumber);
        Serial.println("The port number must be from 0 to 7 on the I2C expansion bus.");
        return;
    }

    Wire.beginTransmission(_mainAddr);
    Wire.write(1 << portNumber);
    Wire.endTransmission();
}

/*
gets the actual hexadecimal address of the I2C expansion
board
*/
uint8_t* I2CExpansion::GetMainAddressHex()
{
    return &_mainAddr;
}

/*
scans the ports of the I2C bus and prints the results
to the serial monitor
*/
void I2CExpansion::ScanPorts()
{
    for (uint8_t t=0; t<8; t++)
    {
      this->SelectPort(t);
      Serial.print("I2C Bus Port #");
      Serial.println(t);

      for (uint8_t addr = 0; addr<=127; addr++)
      {
        if (addr == *(this->GetMainAddressHex()))
        {
            continue;
        }

        uint8_t data;
        if (!twi_writeTo(addr, &data, 0, 1, 1))
        {
           Serial.print("Found Device with address 0x");
           Serial.println(addr,HEX);
        }
      }
    }
}
