#pragma once
#ifndef ACCEL_H
#define ACCEL_H

#include "../../infac/Sensor3D.h"


class Accel : public Sensor3D, public DebugItem {
public:
    Accel() {}
    virtual String getClassName(){return "Accel";}
    virtual String getDebugMsg(bool raw=false) {return Sensor3D::toString();}
};

#endif