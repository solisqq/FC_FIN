#pragma once
#ifndef SDCARD_H
#define SDCARD_H
#include <Arduino.h> 
#include <SPI.h> 
#include <SD.h>
#include "../../main/Settings.h"
#include "../../utilities/Output/Output.h"

class SDCard
{
private:
public:
    SDCard() {}
    ~SDCard() {}
    
    String readSettings(SPIClass *SPIConn){
        SD.begin(Settings::SD::CSPin, *SPIConn);
        Output::info("Loading data from memory card...");
        delay(300);
        String toRet="";
        File file = SD.open("/set.txt");
        if(!file){Output::info("Failed to open SDCard.");return "ERR";}
        while(file.available()) toRet+=static_cast<char>(file.read());
        file.close();
        SD.end();
        Output::info("Data loaded.");
        return toRet;
    }
    void writeSettings(SPIClass *SPIConn, String msg) {
        Output::info("Saving data to memory card...");
        SD.begin(Settings::SD::CSPin, *SPIConn);
        delay(300);
        File file = SD.open("/set.txt", FILE_WRITE);
        if(!file)return;
        file.print(msg);
        file.close();
        SD.end();
        Output::info("Saved.");
    }
};



#endif