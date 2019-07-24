#pragma once
#include "startup.h"

void mainLoop()
{
    imu.update();

    if (rx.Switch[1].get() > 0)
    {
        if (imu.dataReady == true)
        {
            copter.setState(Steering::State::Flying);
            imu.dataReady = false;
        }
    }
    else{
        copter.setState(Steering::State::Idle);
        copter.stop();
    }

    if (debugTimer.IsReady())
        debugger.Show();

    if (rxTimer.IsReady())
        rx.update();

    if (Serial.available())
    {
        char c = Serial.read();
        if (c == '\n')
        {
            cmd.doActionOnCMD(command);
            command = "";
        }
        else
            command += c;
    }
}