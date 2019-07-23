#pragma once
#include "startup.h"

void mainLoop()
{
    imu.update();
    
    //if(rx.Switch[1].get()>0) {
        if(imu.dataReady==true) {
            copter.setThrottle(rx.Throttle.get());
            pid.run(imu.eulers, rx.getPoint3D());
            imu.dataReady=false;
        }
    //}
    
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