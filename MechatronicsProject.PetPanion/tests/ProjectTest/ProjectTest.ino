#ifndef PET_PANION_H
    #define PET_PANION_H
    #include "lib/PetPanion.hpp"
#endif

//devices

MotionSystem* msys;
FoodSystem* fsys;
UI* ui;
SDFileStream* sdfs;
Clock* clock;

//loop variables

long testFreqOpts[4] = {86400, 17280, 8640, 4320};
DateTime date;
float weight;
long curUnixSecs;
long feedingUnixSecs;
long elapsedUnixTime;
long feedCount;
long feedFreq;
char* readBuffer;
// long lastFeedTime;
boolean feedingTimeIsOver;
boolean isFeedingTime;
boolean isAtHome;
/*
% of time between feeding that the robot
will be at the feeding location
*/
const float feedingDurationRatio = 0.5;

void setup()
{
    Wire.begin();
    Serial.begin(9600);

    //setting servo options
    byte pin = 6;
    ServoMotorOptions* servOpts = new ServoMotorOptions(pin);

    //setting load cell options
    byte dOutPin = 7;
    byte sClockPin = 8;
    byte gain = 128;
    float calibFac = -7050.0;
    LoadCellOptions* lcOpts =
        new LoadCellOptions(dOutPin, sClockPin, gain, calibFac);

    //color sensor array options
    byte numSens = 3;
    byte ledPins[] = {22,23,24};
    byte cSenPorts[] = {0,1,2};
    IntegrationTime intTimes[] = {IT_101, IT_101, IT_101};
    Gain colorGains[] = {G_16x, G_16x, G_16x};
    ColorSensorArrayOptions csaOpts = ColorSensorArrayOptions(numSens, cSenPorts, intTimes,
            colorGains, ledPins);

    //motion system options
    float csHigh = 150;
    float csLow = 100;
    float accErr = 2;
    int spdStr = 30;
    int spdSlowTurn = 30;
    int spdFastTurn = 50;
    MotionSystemOptions* msysOpts = new MotionSystemOptions(csHigh, csLow,
        spdStr, spdSlowTurn, spdFastTurn);

    //building IR sensors
    byte frontIrPin = 2;
    byte backIrPin = 3;
    IRSensor* irFront = new IRSensor(frontIrPin);
    IRSensor* irBack = new IRSensor(backIrPin);

    //building the I2C expansion bus
    I2CExpansion* i2c = new I2CExpansion(1);

    //building the clock
    byte clockI2CPort = 3;
    DateTime setupDate = DateTime(2019, 1, 1, 0, 0, 0);
    clock = new Clock(i2c, clockI2CPort);

    //building the motion system
    byte leftPin = 4;
    byte rightPin = 5;
    msys = new MotionSystem(leftPin, rightPin, msysOpts, i2c, csaOpts,
        irFront, irBack);

    //building the food system
    int degsOpen = 0;
    int degsClose = 75;
    float weightSP = 0.25;
    float errTol = 0.1;
    long minDelay = 150;
    long initDelay = 2500;
    fsys =
        new FoodSystem(degsOpen, degsClose, weightSP, errTol, minDelay,
            initDelay, lcOpts, servOpts);

    //building the UI
    byte pin1 = 25;
    byte pin2 = 26;
    ui = new UI(pin1, pin2);

    //building the SD file stream
    byte ssPin = 53;
    const char* fileName = "DATA.CSV";
    sdfs = new SDFileStream(ssPin, fileName);

    //clock setup
    if (!clock->Setup())
    {
        Serial.println("Clock not found.");
        while (1);
    }
    clock->Adjust(setupDate);

    //food system setup
    if (!(fsys->Setup()))
    {
        Serial.println("Food system isn't setup correctly.");
        while(1);
    }
    fsys->ZeroScale();

    //mottion system setup
    if (!(msys->Setup()))
    {
        Serial.println("Motion system didn't setup properly.");
        while(1);
    }
    msys->DeactivateLeds();

    //UI setup
    ui->Setup();
    ui->SetFrequencyOptions(testFreqOpts);

    //variable initialization
    feedFreq = 3;
    feedCount = 0;
    feedingUnixSecs = 0;
    isAtHome = true;
    feedingTimeIsOver = true;
}

void loop()
{
    date = clock->Now();
    curUnixSecs = date.unixtime();
    elapsedUnixTime = curUnixSecs - feedingUnixSecs;

    Serial.print("Current DateTime:");
    Serial.print(date.month(), DEC);
    Serial.print('/');
    Serial.print(date.day(), DEC);
    Serial.print('/');
    Serial.print(date.year(), DEC);
    Serial.print(' ');
    Serial.print(date.hour(), DEC);
    Serial.print(':');
    Serial.print(date.minute(), DEC);
    Serial.print(':');
    Serial.print(date.second(), DEC);
    Serial.println();

    //determines when feeding time begins
    isFeedingTime = DetermineFeedingTime(elapsedUnixTime, feedFreq);

    if (isFeedingTime)
    {
        Serial.println("It is feeding time.");
    }
    else
    {
        Serial.println("It is not feeding time.");
    }

    //determines when the time allocated towards feeding time has expired
    feedingTimeIsOver = DetermineEndOfFeedingTime(elapsedUnixTime, feedFreq,
        feedCount, feedingDurationRatio);

    if (feedingTimeIsOver)
    {
        Serial.println("Feeding time is over.");
    }
    else
    {
        Serial.println("Feeding time is not over.");
    }

    if (isFeedingTime && isAtHome)
    {
        Serial.println("Dispensing food.");
        //food dispensing algorithm
        // fsys->DispenseFood();

        Serial.println("Writing data to DATA.CSV.");
        //writes the datetime & weight data to a file on the sd card
        weight = 5.0;//fsys->GetLastMeasuredWeight();
        WriteWeightData(sdfs, date, weight);

        //read the contents of the sd card
        sdfs->OpenStream();
        sdfs->OpenFile(Read);
        readBuffer = sdfs->FileRead();
        Serial.print(readBuffer);
        sdfs->CloseFile();
        sdfs->CloseStream();

        //determines if feedcount must be reset
        if (feedCount == feedFreq)
        {
            Serial.println("Feeding count is reset.");
            feedCount = 0;
        }
        else
        {
            Serial.println("Feeding count is increased.");
            feedCount++;
        }

        Serial.println("Robot is traveling to the feeding location.");
        //robot travels to the feeding location
        msys->GotoFeedingLocation();
        isAtHome = false;
        feedingTimeIsOver = false;
        feedingUnixSecs = curUnixSecs;
    }

    if (!isAtHome && feedingTimeIsOver)
    {
        Serial.println("Robot is traveling back home.");
        //robot travels home
        msys->GoHome();
        isAtHome = true;
    }

    feedFreq = ui->GetFrequency();
    Serial.print("Feeding frequency = ");
    Serial.print(feedFreq);
    Serial.println(" per day.");
    Serial.print("\n\n\n\n");
    delay(1000);
}
