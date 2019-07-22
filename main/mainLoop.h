#pragma once
#include "startup.h"

void mainLoop()
{
    imu.update();

    if(debugTimer.IsReady()) 
        debugger.Show();

    if(rxTimer.IsReady())
        rx.update(); 

    if(Serial.available()) {
        char c = Serial.read();
        if(c=='\n'){
            cmd.doActionOnCMD(command);
            command="";
        }
        else command+=c;
    }
}