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
    Vector<float> getDegPerSec() {
        Vector<float> converted;
        converted.x = static_cast<Average<int16_t>*>(values.x.filters.back->val)->getAvg();
        converted.y = static_cast<Average<int16_t>*>(values.y.filters.back->val)->getAvg();
        converted.z = static_cast<Average<int16_t>*>(values.z.filters.back->val)->getAvg();
        converted /= Settings::Gyro::sensitivity;
        return converted;
    }
    void setAvgFilter(int count) {
        Sensor3D::values.x.addFilter(new Average<int16_t>(count));
        Sensor3D::values.y.addFilter(new Average<int16_t>(count));
        Sensor3D::values.z.addFilter(new Average<int16_t>(count));
    }
};

#endif