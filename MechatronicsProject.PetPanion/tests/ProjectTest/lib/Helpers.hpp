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
boolean DetermineFeedingTime(float elapsedUnixTime, float feedFreq)
{
    //#seconds in a day / freq = # seconds between each feeding
    float secPerFeed = (24.0 * 3600.0) / feedFreq;

    Serial.print("Seconds per feed: ");
    Serial.println(secPerFeed);

    return elapsedUnixTime >= secPerFeed;
}

//determines when the time allocated towards feeding time has expired
boolean DetermineEndOfFeedingTime(float elapsedTime, float feedFreq,
    float feedCount, float feedingDurationRatio)
{
    //#seconds in a day / freq = # seconds between each feeding
    float secPerFeed = (24.0 * 3600.0) / feedFreq;

    //the feeding hours that have already passed
    // float lastFeedingTime = feedCount * feedFreq;

    Serial.print("Elapsed Seconds = ");
    Serial.println(elapsedTime);
    Serial.print("Feeding time duration = ");
    Serial.println((feedingDurationRatio * secPerFeed));

    return elapsedTime >= (feedingDurationRatio * secPerFeed);
}

//writes the datetime & weight data to a file on the sd card
void WriteWeightData(SDFileStream* sdfs, DateTime curDateTime,
    float weight)
{
    IOSetting w = Write;
    char* dataBuffer;
    char* floatBuffer;

    floatBuffer = (char*)malloc(5*sizeof(char));
    dataBuffer = (char*)malloc(24*sizeof(char));
    dtostrf(weight, 5, 2, floatBuffer);
    char* dataFormat = "%02d-%02d-%4d %02d:%02d,%.5s\n\0";

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
            floatBuffer
        );

    //writing the buffer to the file
    sdfs->OpenStream();
    sdfs->OpenFile(w);
    sdfs->FileWrite(dataBuffer);
    sdfs->CloseFile();
    sdfs->CloseStream();
}
