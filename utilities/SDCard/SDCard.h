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
    void init(SPIClass *SPIConn) {
        SD.begin(Settings::SD::CSPin, *SPIConn);
        delay(300);
    }
    ~SDCard() {}
    
    String readSettings(){
        String toRet="";
        String path = "/set.txt";
        File file = SD.open(path);
        if(!file){Output::info("Failed to open SDCard.");return "ERR";}
        while(file.available()) toRet+=file.read();
        file.close();
        return toRet;
    }
};



#endif