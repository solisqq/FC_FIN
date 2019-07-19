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
        if(Serial.read()=='a') {
            cmd.doActionOnCMD("accel");
        }
    }
}