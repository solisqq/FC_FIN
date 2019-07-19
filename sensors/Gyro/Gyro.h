#pragma once
#ifndef GYRO_H
#define GYRO_H

#include "../../infac/Sensor3D.h"
#include "../../filters/Average.h"

class Gyro : public Sensor3D, public DebugItem {
public:
    Gyro() {}
    virtual String getClassName(){return "Gyro";}
    virtual String getDebugMsg(bool raw=false) {return Sensor3D::toString();}
    /*Point3D<float> convertToDegPerSec(double timeInSec) {
        Point3D<float> converted;
        converted.x.update((values.x.value/Settings::gyroSensitivity)/timeInSec);
    }*/
    void setAvgFilter(int count) {
        Sensor3D::values.x.addFilter(new Average<int16_t>(count));
        Sensor3D::values.y.addFilter(new Average<int16_t>(count));
        Sensor3D::values.z.addFilter(new Average<int16_t>(count));
    }
};

#endif