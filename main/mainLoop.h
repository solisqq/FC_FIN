#pragma once
#include "startup.h"

void mainLoop()
{
    if(debugTimer.IsReady()) 
        debugger.Show();
    if(Serial.available()) {
        if(Serial.read()=='a') {
            cmd.doActionOnCMD("debug");
        }
    }
}