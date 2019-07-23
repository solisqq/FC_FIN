#pragma once
#ifndef STEERING_H
#define STEERING_H

#include "Engine.h"

class Steering
{
private:
    Engine frontLeft;
    Engine frontRight;
    Engine backLeft;
    Engine backRight;
    Engine **engines;
public:
    Steering(/* args */) {
        engines = new Engine*[4];
        engines[0] = &frontLeft;
        engines[1] = &frontRight;
        engines[2] = &backLeft;
        engines[3] = &backRight;
    }
    void init() {
        frontLeft.Init(Settings::Engines::fl);
        frontRight.Init(Settings::Engines::fr);
        backLeft.Init(Settings::Engines::bl);
        backRight.Init(Settings::Engines::br);

        delay(200);
    }
    void setThrottle(int throttleVal) {
        for(int i=0; i<4; i++) 
            engines[i]->SetSpeed(throttleVal);
    }
};

#endif