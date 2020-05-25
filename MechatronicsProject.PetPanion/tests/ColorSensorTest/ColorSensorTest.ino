#ifndef PET_PANION_H
    #define PET_PANION_H
    #include "lib/PetPanion.hpp"
#endif

ColorSensor* colSen;
float* rgb;
byte ledPin = 7;

void setup()
{
    Serial.begin(9600);
    pinMode(ledPin,OUTPUT);

    colSen = new ColorSensor(IT_700, G_60x, ledPin);

    if (colSen->Setup())
    {
        Serial.println("Found color sensor.");
    }
    else
    {
      Serial.println("No color sensor connected.");
      while(1);
    }
}

void loop()
{
    rgb = colSen->GetRGB();

    Serial.print("R: ");
    Serial.print(rgb[0]);
    Serial.print(" G: ");
    Serial.print(rgb[1]);
    Serial.print(" B: ");
    Serial.println(rgb[2]);

     colSen->LedOn();
     delay(500);
     colSen->LedOff();
     delay(500);
}
