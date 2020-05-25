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
boolean DetermineFeedingTime(float curHour, float feedFreq, byte feedCount)
{
    //24 hours / freq = # hours between each feed
    float hrsPerFeed = 24.0 / feedFreq;

    //the feeding hours that have already passed
    float lastFeedingHr = feedCount * feedFreq;

    return curHour >= (hrsPerFeed + lastFeedingHr);
}

//determines when the time allocated towards feeding time has expired
boolean DetermineEndOfFeedingTime(float curHour, float feedFreq,
    float lastFeedHour, float feedingDurationRatio)
{
    //24 hours / freq = # hours between each feed
    float hrsPerFeed = 24.0 / feedFreq;

    return curHour >= (lastFeedHour + feedingDurationRatio * hrsPerFeed);
}

//writes the datetime & weight data to a file on the sd card
void WriteWeightData(SDFileStream* sdfs, DateTime curDateTime,
    float weight)
{
    IOSetting w = Write;
    char* dataBuffer;
    const char* dataFormat = "%2d-%2d-%4d %2d:%2d:%2d,%4.2f\n";

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

    //writing the buffer to the file
    sdfs->OpenStream();
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
    sdfs->CloseFile();
    sdfs->CloseStream();
}
