#pragma once
#include "startup.h"

void mainLoop()
{
    imu.update();

    if (rxTimer.IsReady())
            rx.update();
    if (debugTimer.IsReady())
            debugger.Show();
            
    if (rx.Switch[1].get() > 0.8)
    {
        if (imu.dataReady == true)
        {
            copter.setState(Steering::State::Flying);
            imu.dataReady = false;
        }
    }
    else {
        copter.setState(Steering::State::Idle);
        copter.stop();
        
        if (Serial.available())
        {
            char c = Serial.read();
            if (c == '\n')
            {
                cmd.doActionOnCMD(command);
                command = "";
            } else command += c;
        }
    }
}