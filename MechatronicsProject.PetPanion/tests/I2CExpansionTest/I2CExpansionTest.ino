#ifndef PET_PANION_H
    #define PET_PANION_H
    #include "lib/PetPanion.hpp"
#endif

const byte ledPin1 = 22;
const byte ledPin2 = 23;
const byte ledPin3 = 24;

const byte cSen1Port = 0;
const byte cSen2Port = 1;
const byte cSen3Port = 2;
const byte rtcPort = 3;

I2CExpansion* i2cExp;

ColorSensor* colSen1;
ColorSensor* colSen2;
ColorSensor* colSen3;
float* rgb1;
float* rgb2;
float* rgb3;

RTC* rtc;
DateTime now;

float* TestRGB(ColorSensor* colSen)
{
    colSen->LedOff();
    delay(100);
    colSen->LedOn();
    delay(50);
    return colSen->GetRGB();
}

void setup()
{
    Wire.begin();
    Serial.begin(9600);

    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);
    pinMode(ledPin3, OUTPUT);

    i2cExp = new I2CExpansion(1);

    colSen1 = new ColorSensor(IT_154, G_60x, ledPin1);
    i2cExp->SelectPort(cSen1Port);

    if (!colSen1->Setup())
    {
      Serial.println("Color Sensor 1 not connected.");
    }
    colSen1->LedOn();

    colSen2 = new ColorSensor(IT_154, G_60x, ledPin2);
    i2cExp->SelectPort(cSen2Port);

    if (!colSen2->Setup())
    {
      Serial.println("Color Sensor 2 not connected.");
    }
    colSen2->LedOn();

    colSen3 = new ColorSensor(IT_154, G_60x, ledPin3);
    i2cExp->SelectPort(cSen3Port);

    if (!colSen3->Setup())
    {
      Serial.println("Color Sensor 3 not connected.");
    }
    colSen3->LedOn();

    rtc = new RTC();
    i2cExp->SelectPort(rtcPort);
    rtc->Setup();
    rtc->Adjust(DateTime(2019, 1, 1, 0, 0, 0));

    if (!rtc->Setup())
    {
        Serial.println("RTC not connected.");
        while (1);
    }

    i2cExp->ScanPorts();

    Serial.print("I2C Expansion Address: ");
    Serial.println(*(i2cExp->GetMainAddressHex()),HEX);
    Serial.println("\n\n");
}

void loop()
{
    i2cExp->SelectPort(cSen1Port);
    rgb1 = TestRGB(colSen1);

    i2cExp->SelectPort(cSen2Port);
    rgb2 = TestRGB(colSen2);

    i2cExp->SelectPort(cSen3Port);
    rgb3 = TestRGB(colSen3);

    i2cExp->SelectPort(rtcPort);
    now = rtc->Now();

    Serial.println("Color Sensor 1 RGB Values:");
    Serial.print("R: ");
    Serial.print(rgb1[0]);
    Serial.print(" G: ");
    Serial.print(rgb1[1]);
    Serial.print(" B: ");
    Serial.println(rgb1[2]);

    Serial.println("Color Sensor 2 RGB Values:");
    Serial.print("R: ");
    Serial.print(rgb2[0]);
    Serial.print(" G: ");
    Serial.print(rgb2[1]);
    Serial.print(" B: ");
    Serial.println(rgb2[2]);

    Serial.println("Color Sensor 3 RGB Values:");
    Serial.print("R: ");
    Serial.print(rgb3[0]);
    Serial.print(" G: ");
    Serial.print(rgb3[1]);
    Serial.print(" B: ");
    Serial.println(rgb3[2]);

    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print('/');
    Serial.print(now.year(), DEC);
    Serial.print(" ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println("\n");
    delay(1000);
}
