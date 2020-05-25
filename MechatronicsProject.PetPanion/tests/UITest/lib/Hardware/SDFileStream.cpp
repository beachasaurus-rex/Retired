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
    this->_file = 0;
}

//opens a stream to communicate with the SD card
boolean SDFileStream::OpenStream()
{
    // return SD.begin(this->_ssPin);
    return SD.begin();
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
            this->_file = &temp;
            break;
        case Read:
            temp = SD.open(this->_fileName, FILE_READ);
            this->_file = &temp;
            break;
    }
}

//closes the file with the stored filename
void SDFileStream::CloseFile()
{
    this->_file->close();
    this->_file = 0;
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
    boolean fileIsClosed = this->_file == 0;

    if (fileExists && fileIsClosed)
    {
        SD.remove(this->_fileName);
    }
    else if (fileExists && !fileIsClosed)
    {
        this->CloseFile();
        SD.remove(this->_fileName);
    }
}

//creates the file with the stored filename
void SDFileStream::CreateFile(IOSetting ioSetting)
{
    if (!(this->FileExists()))
    {
        this->OpenFile(ioSetting);
    }
}

//writes the given buffer to the file with the stored filename
void SDFileStream::FileWrite(char* buffer)
{
    boolean fileExists = this->FileExists();
    boolean fileIsOpen = this->_file != 0;

    if (fileExists && fileIsOpen)
    {
        this->_file->print(buffer);
    }
}

//reads the file from the stored filename
char* SDFileStream::FileRead()
{
    boolean fileExists = this->FileExists();
    boolean fileIsOpen = this->_file != 0;

    if (fileExists && fileIsOpen)
    {
        long numChars = 0;

        //count the number of characters in the file
        while (this->_file->available())
        {
            char temp = this->_file->read();
            numChars++;
        }

        char* buffer = (char*)malloc(numChars * sizeof(char));
        long i = 0;
        //store the data in the buffer
        while (this->_file->available())
        {
            buffer[i] = this->_file->read();
            i++;
        }

        return buffer;
    }

    return strdup("");
}
