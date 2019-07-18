#pragma once
#include "startup.h"

void mainLoop()
{
    if(debugTimer.IsReady()) 
        debugger.Show();

    if(rxTimer.IsReady())
        rx.update(); 

    if(imuTimer.IsReady()) 
        imu.update();

    if(Serial.available()) {
        if(Serial.read()=='a') {
            cmd.doActionOnCMD("gyro");
        }
    }
}