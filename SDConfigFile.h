#ifndef SDConfigFile_h
#define SDConfigFile_h

/*
 * SD card configuration file reading library
 *
 * Copyright (c) 2014, 2017 Bradford Needham
 * (@bneedhamia, https://www.needhamia.com )
 * Licensed under LGPL version 2.1
 * a version of which should have been supplied with this file.
 *
 * The library supports one #define:
 *   #define SDCONFIGFILE_DEBUG 1 // to print file error messages.
 */

#include <Arduino.h>
#include <SD.h>

class SDConfigFile {
  private:
    File _file;            // the open configuration file
    boolean _atEnd;        // If true, there is no more of the file to read.
    char *_line;           // the current line of the file (see _lineLength)
                           // Allocated by begin().
    uint8_t _lineSize;     // size (bytes) of _line[]
    uint8_t _lineLength;   // length (bytes) of the current line so far.
    uint8_t _valueIdx;     // position in _line[] where the value starts
                           //  (or -1 if none)
                           // (the name part is at &_line[0])
  
  public:
    boolean begin(const char *configFileName, uint8_t maxLineLength);
    void end();
    boolean readNextSetting();
    boolean nameIs(const char *name);
    const char *getName();
    const char *getValue();
    int getIntValue();
    boolean getBooleanValue();
    char *copyValue();
};
#endif
