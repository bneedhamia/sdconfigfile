# SDConfigFile

## Introduction

SDConfigFile is an Arduino library to read Sketch settings from a configuration file on an SD card.

I wrote the library so that I didn't have to hard-code private WiFi settings in my Sketches.  Instead, I have a config.cfg file on an SD card, that contains things like:

    ssid=wickedOz
    password=flyingMonkeys

Now I can change the WiFi settings, or any other configuration, by simply editing the SD card's **config.cfg** file.

## Installation

To install SDConfigFile on Windows:

1. Run git bash (or whatever git client you like)
1. cd Documents/Arduino/libraries
1. git clone https://github.com/bneedhamia/sdconfigfile.git SDConfigFile
1. restart your Arduino IDE

To install SDConfigFile on Linux:

1. cd sketchbook/libraries
1. git clone https://github.com/bneedhamia/sdconfigfile.git SDConfigFile
1. restart your Arduino IDE

## To use

See **examples/SDConfigFileExample** for a simple example Sketch and its .cfg file.  See readConfiguration() in that sketch for the code that reads the settings from the .cfg file.

The basic flow of reading a configuration file is:

    #include <SD.h>
    #include <SDConfigFile.h>

    SDConfigFile cfg;
    
    SD.begin(...);
    cfg.begin(...);
    while (cfg.readNextSetting()) {
      if (cfg.nameIs("mySetting1")) {
        call cfg.copyValue(),
             cfg.getBooleanValue(), or
             cfg.getIntValue(), as appropriate;
      }
      ...do the same for the other setting names.
    }
    cfg.end();
