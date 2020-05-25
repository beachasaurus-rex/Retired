#ifndef PET_PANION_H
    #define PET_PANION_H
    #include "lib/PetPanion.hpp"
#endif

UI* ui;

void setup()
{
    long testFreqOpts[4] = {86400, 17280, 8640, 4320};

    Serial.begin(9600);
    byte pin1 = 25;
    byte pin2 = 26;
    ui = new UI(pin1, pin2);
    ui->Setup();
    ui->SetFrequencyOptions(testFreqOpts);
}

void loop()
{
    Serial.print("Feeding frequency is ");
    Serial.print(ui->GetFrequency());
    Serial.println(" times per day.");
}
