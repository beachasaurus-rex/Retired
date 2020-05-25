#ifndef PET_PANION_H
    #define PET_PANION_H
    #include "lib/PetPanion.hpp"
#endif

ServoMotor* servo;

void setup()
{
    Serial.begin(9600);
    servo = new ServoMotor(5);
    servo->Attach();
}

void loop()
{
    if (!(servo->IsAttached()))
    {
        servo->Attach();
        while(!(servo->IsAttached()));
    }

    servo->Rotate(0);
    Serial.println("Open");
    delay(2500);
    servo->Rotate(90);
    Serial.println("Close");
    delay(2500);
    servo->Detach();
    delay(5000);
}
