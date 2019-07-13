#pragma once
#ifndef IMU_H
#define IMU_H

#include "../infac/Sensor3D.h"


class Gyro : public Sensor3D {
public:
    Gyro() {}
    void initialize() {
    }
    
};

#endif