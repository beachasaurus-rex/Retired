#ifndef SD_FILE_STREAM_H
    #define SD_FILE_STREAM_H
    #include "SDFileStream.hpp"
#endif

//constructor
SDFileStream::SDFileStream(byte slaveSelectPin,
    const char* fileName)
{
    //set instance variables
    this->_ssPin = slaveSelectPin;
    this->_fileName = fileName;
}

//opens a stream to communicate with the SD card
boolean SDFileStream::OpenStream()
{
    return SD.begin(this->_ssPin);
}

//closes the stream that communicates with the SD card
void SDFileStream::CloseStream()
{
    SD.end();
}

//opens the file with the stored filename
void SDFileStream::OpenFile(IOSetting ioSetting)
{
    File temp;
    switch (ioSetting)
    {
        case Write:
            temp = SD.open(this->_fileName, FILE_WRITE);
            this->_file = temp;
            break;
        case Read:
            temp = SD.open(this->_fileName, FILE_READ);
            this->_file = temp;
            break;
    }
}

//closes the file with the stored filename
void SDFileStream::CloseFile()
{
    this->_file.close();
}

//checks if the file with the stored filename exists
boolean SDFileStream::FileExists()
{
    return SD.exists(this->_fileName);
}

//deletes the file with the stored filename
void SDFileStream::DeleteFile()
{
    boolean fileExists = this->FileExists();

    if (fileExists && this->_file)
    {
        SD.remove(this->_fileName);
    }
    else if (fileExists && !(this->_file))
    {
        this->CloseFile();
        SD.remove(this->_fileName);
    }
}

//writes the given buffer to the file with the stored filename
void SDFileStream::FileWrite(char* buffer)
{
    if (this->_file)
    {
        this->_file.print(buffer);
    }
}

//reads the file from the stored filename
char* SDFileStream::FileRead()
{
    if (this->_file)
    {
        long lenbuff = 0;
        //start from the top of the file
        this->_file.seek(0);
        //count the number of characters in the file
        while (this->_file.available())
        {
            this->_file.read();
            lenbuff++;
        }

        //make a buffer
        char* buffer = (char*)malloc(lenbuff * sizeof(char));
        this->_file.seek(0);
        //get all of the characters into the buffer
        this->_file.read(buffer, lenbuff);
        buffer[lenbuff] = '\0';
        return buffer;
    }

    return strdup("");
}
