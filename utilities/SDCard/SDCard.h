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
        delay(300);
        String toRet="";
        String path = "/set.txt";
        File file = SD.open(path);
        if(!file){Output::info("Failed to open SDCard.");return "ERR";}
        while(file.available()) toRet+=static_cast<char>(file.read());
        file.close();
        SD.end();
        return toRet;
    }
};



#endif