#pragma once
#include "startup.h"

void mainLoop()
{
    imu.update();

    if (rxTimer.IsReady())
            rx.update();
    if (debugTimer.IsReady())
            debugger.Show();

    if (rx.isSafetySwitchOn())
    {
        if(rx.isThrottleHigh() && copter.currentState == Steering::State::Idle) {
            copter.setState(Steering::State::Idle);
            copter.stop();
            Output::info("Throttle high, unable to start");
        } else {
            if (imu.dataReady == true)
            {
                copter.setState(Steering::State::Flying);
                imu.dataReady = false;
            }
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