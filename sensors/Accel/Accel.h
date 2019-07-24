#pragma once
#ifndef ACCEL_H
#define ACCEL_H

#include "../../infac/Sensor3D.h"
#include "../MPU9250.h"

class Accel : public Sensor3D, public DebugItem {
public:
    Accel();
    virtual String getClassName();
    virtual String getDebugMsg(bool raw=false);
    Vector<float> getEulers(Point3D<float> backup);
	virtual void updateByMPU(MPU9250 *mpu);
};

#include "Accel.cpp"

#endif