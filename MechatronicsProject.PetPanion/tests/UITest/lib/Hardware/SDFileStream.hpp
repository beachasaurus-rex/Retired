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
        /*
        description: constructor
        inputs:
            1. slave-select pin number
            2. file name
        returns: instance of an SD file stream object
        */
        SDFileStream(byte, const char*);
        /*
        description: opens a stream to communicate with the SD card
        inputs: none
        returns: true if the stream was opened
        */
        boolean OpenStream(void);
        /*
        description: closes the stream that communicates with the SD card
        inputs: none
        returns: none
        */
        void CloseStream(void);
        /*
        description: opens the file with the stored filename
        inputs: IO setting
        returns: none
        */
        void OpenFile(IOSetting);
        /*
        description: closes the file with the stored filename
        inputs: none
        returns: none
        */
        void CloseFile(void);
        /*
        description: deletes the file with the stored filename
        inputs: none
        returns: none
        */
        void DeleteFile(void);
        /*
        description: checks if the file with the stored filename exists
        inputs: none
        returns: true if the file exists
        */
        boolean FileExists(void);
        /*
        description: writes the given buffer to the file with
                     the stored filename
        inputs: a buffer
        returns: none
        */
        void FileWrite(char*);
        /*
        description: reads the file from the stored filename
        inputs: none
        returns: a buffer
        */
        char* FileRead(void);
        /*
        description: creates the file with the stored filename
        inputs: IO setting
        returns: none
        */
        void CreateFile(IOSetting);
};
