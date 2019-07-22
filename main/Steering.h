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

        frontLeft.Init(Settings::Engines::fl);
        frontLeft.Init(Settings::Engines::fr);
        frontLeft.Init(Settings::Engines::bl);
        frontLeft.Init(Settings::Engines::br);
    }
    ~Steering();
};

#endif