#pragma once
#ifndef GYRO_H
#define GYRO_H

#include "../../infac/Sensor3D.h"


class Gyro : public Sensor3D, public DebugItem {
public:
    Gyro() {}
    void initialize() {}
    virtual String getClassName(){return "Gyro";}
    virtual String getDebugMsg(bool raw=false) {return Sensor3D::toString();}
};

#endif