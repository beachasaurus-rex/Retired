#ifndef PET_PANION_H
    #define PET_PANION_H
    #include "lib/PetPanion.hpp"
#endif

SDFileStream* fs;
byte ssPin = 53;
char* buff;
boolean isOpen;
float weight = 1.2;

void setup()
{
    Serial.begin(9600);

    fs = new SDFileStream(ssPin, "test.csv");
}

void loop()
{
    // buff = (char*)"HELLO,WORLD\n\0";

    isOpen = fs->OpenStream();
    if (!isOpen)
    {
        Serial.println("Failed to communicate with SD card.");
        while(1);
    }

    fs->OpenFile(Write);
    for (int i = 0; i < 1; i++)
    {
        char* dataBuffer;
        char* floatBuffer;

        floatBuffer = (char*)malloc(5*sizeof(char));
        dataBuffer = (char*)malloc(24*sizeof(char));
        dtostrf(weight, 5, 2, floatBuffer);
        char* dataFormat= "%02d-%02d-%4d %02d:%02d,%s\n\0";

        //writing the weight & datetime to a buffer in csv format
        sprintf
            (
                dataBuffer,
                dataFormat,
                1,
                1,
                2019,
                3,
                26,
                floatBuffer
            );

        fs->FileWrite(dataBuffer);
    }
    fs->CloseFile();

    fs->OpenFile(Read);
    buff = fs->FileRead();
    fs->CloseFile();
    fs->DeleteFile();
    fs->CloseStream();

    Serial.print(buff);
    delay(5000);
}
