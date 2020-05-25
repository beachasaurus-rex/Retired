#ifndef PET_PANION_H
    #define PET_PANION_H
    #include "lib/PetPanion.hpp"
#endif

I2CExpansion* i2cExp;

ColorSensorArray* colSenArr;
float** rgbArr;

void setup()
{
    byte numSens = 3;
    byte ledPins[] = {22,23,24};
    byte cSenPorts[] = {0,1,2};
    IntegrationTime intTimes[] = {IT_101, IT_101, IT_101};
    Gain colorGains[] = {G_16x, G_16x, G_16x};

    Wire.begin();
    Serial.begin(9600);

    pinMode(ledPins[0], OUTPUT);
    pinMode(ledPins[1], OUTPUT);
    pinMode(ledPins[2], OUTPUT);

    i2cExp = new I2CExpansion(1);

    ColorSensorArrayOptions arrOpts = ColorSensorArrayOptions(numSens, cSenPorts,
      intTimes, colorGains, ledPins);

    colSenArr = new ColorSensorArray(i2cExp, arrOpts);

    if (!(colSenArr->Setup()))
    {
        Serial.println("Unable to connect to color sensor array.");
        while(1);
    }

    colSenArr->ActivateLeds();
    i2cExp->ScanPorts();

    Serial.print("I2C Expansion Address: ");
    Serial.println(*(i2cExp->GetMainAddressHex()),HEX);
    Serial.println("\n\n");
}

void loop()
{
    rgbArr = colSenArr->TestReadRGBValues();

    for (int i = 0; i < colSenArr->Count(); i++)
    {
        Serial.print("Color Sensor ");
        Serial.print(i+1);
        Serial.println(" RGB Values:");
        Serial.print("R: ");
        Serial.print(rgbArr[i][0]);
        Serial.print(" G: ");
        Serial.print(rgbArr[i][1]);
        Serial.print(" B: ");
        Serial.println(rgbArr[i][2]);
    }

    Serial.println("\n");
    delay(1000);
}
