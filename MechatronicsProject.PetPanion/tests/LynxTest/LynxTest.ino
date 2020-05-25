#ifndef PET_PANION_H
    #define PET_PANION_H
    #include "lib/PetPanion.hpp"
#endif

/*
S1 = RIGHT MOTORS
S2 = LEFT MOTORS
*/

Lynx* lynx;

void setup()
{
    Serial.begin(9600);

    byte leftPin = 6;
    byte rightPin = 7;
    lynx = new Lynx(leftPin, rightPin);
    lynx->Attach();
}

void loop()
{
    Serial.println("Lynx moving forward.");
    lynx->Forward(20);
    delay(2000);

    Serial.println("Lynx moving backward.");
    lynx->Backward(20);
    delay(2000);

    Serial.println("Lynx moving forward & left.");
    lynx->TurnForward(20, 50);
    delay(2000);

    Serial.println("Lynx moving forward & right.");
    lynx->TurnForward(50, 20);
    delay(2000);

    Serial.println("Lynx moving backward & left.");
    lynx->TurnBackward(20, 50);
    delay(2000);

    Serial.println("Lynx moving backward & right.");
    lynx->TurnBackward(50, 20);
    delay(2000);

    Serial.println("Lynx is stopped.");
    lynx->Stop();
    delay(2000);
}
