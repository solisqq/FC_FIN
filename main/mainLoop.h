#pragma once
#include "startup.h"

void mainLoop()
{
    imu.update();

    if(debugTimer.IsReady()) {
        //Serial.println(imu.compStrX.value,4);
        debugger.Show();
    }
       

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