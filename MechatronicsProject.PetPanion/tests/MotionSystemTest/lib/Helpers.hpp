#ifndef DEPS_H
    #define DEPS_H
    #include "deps.hpp"
#endif

#ifndef SD_FILE_STREAM_H
    #define SD_FILE_STREAM_H
    #include "Hardware/SDFileStream.hpp"
#endif

float RelativeErr(float base, float val)
{
    float out = 0;

    //exclude very small numbers near zero
    if (base <= 1e-7)
    {
        out = 1;
    }
    else
    {
        out = (val - base) / base;
    }

    return out;
}

//determines when feeding time begins
boolean DetermineFeedingTime(float curTime, float feedFreq, byte feedCount)
{
    //#seconds in a day / freq = # seconds between each feeding
    float secPerFeed = (24.0 * 3600.0) / feedFreq;

    //the feeding hours that have already passed
    float lastFeedingTime = feedCount * feedFreq;

    return curTime >= (secPerFeed + lastFeedingTime);
}

//determines when the time allocated towards feeding time has expired
boolean DetermineEndOfFeedingTime(float curTime, float feedFreq,
    float feedCount, float feedingDurationRatio)
{
    //#seconds in a day / freq = # seconds between each feeding
    float secPerFeed = (24.0 * 3600.0) / feedFreq;

    //the feeding hours that have already passed
    float lastFeedingTime = feedCount * feedFreq;

    return curTime >= (lastFeedingTime + feedingDurationRatio * secPerFeed);
}

//writes the datetime & weight data to a file on the sd card
void WriteWeightData(SDFileStream* sdfs, DateTime curDateTime,
    float weight)
{
    IOSetting w = Write;
    char dataBuffer[26];
    const char dataFormat[26] = "%02d-%02d-%4d %02d:%02d:%02d,%4.2f\n";

    //writing the weight & datetime to a buffer in csv format
    sprintf
        (
            dataBuffer,
            dataFormat,
            curDateTime.month(),
            curDateTime.day(),
            curDateTime.year(),
            curDateTime.hour(),
            curDateTime.minute(),
            curDateTime.second(),
            weight
        );

    Serial.println(dataBuffer);
    delay(100);
    //writing the buffer to the file
    sdfs->OpenStream();
    delay(100);
    if (!(sdfs->FileExists()))
    {
        //creates & opens the file for writing purposes
        sdfs->CreateFile(w);
    }
    else
    {
        //opens the file for writing purposes
        sdfs->OpenFile(w);
    }

    sdfs->FileWrite(dataBuffer);
    delay(100);
    sdfs->CloseFile();
    sdfs->CloseStream();
}
