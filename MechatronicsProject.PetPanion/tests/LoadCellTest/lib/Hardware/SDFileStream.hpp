#ifndef ENUMS_H
    #define ENUMS_H
    #include "../Enums.hpp"
#endif

#ifndef DEPS_H
    #define DEPS_H
    #include "../deps.hpp"
#endif

class SDFileStream
{
    private:
        //slave select pin
        byte _ssPin;
        //underlying file stream
        File* _file;
        //stored filename
        const char* _fileName;
    public:
        //constructor
        SDFileStream(byte, const char*);
        //opens a stream to communicate with the SD card
        boolean OpenStream(void);
        //closes the stream that communicates with the SD card
        void CloseStream(void);
        //opens the file with the stored filename
        void OpenFile(IOSetting);
        //closes the file with the stored filename
        void CloseFile(void);
        //deletes the file with the stored filename
        void DeleteFile(void);
        //checks if the file with the stored filename exists
        boolean FileExists(void);
        //writes the given buffer to the file with the stored filename
        void FileWrite(char*);
        //reads the file from the stored filename
        char* FileRead(void);
        //creates the file with the stored filename
        void CreateFile(IOSetting);
};
