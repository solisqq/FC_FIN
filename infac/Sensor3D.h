#pragma once
#ifndef SENSOR3D_H
#define SENSOR3D_H

#include "../math/Point3D/Point3D.h"
#include "../utilities/Timer/Timer.h"
#include "../filters/ButterworthLP.h"
#include "AllowPrint.h"
#include "DebugItem.h"

class Sensor3D : public AllowPrint
{
public:
    Point3D<int16_t> values;

protected:
    Point3D<int16_t> offsets;
    int dataReadFrequency;
    Timer timer;

public:
    Sensor3D() {}
    void initialize(int frequency)
    {
        dataReadFrequency = frequency;
        timer.Init(1000000 / frequency, true);
    }
    void setLowPassFilter(float cutOff)
    {
        values.x.addFilter(new ButterworthLP<int16_t>(dataReadFrequency, cutOff));
        values.y.addFilter(new ButterworthLP<int16_t>(dataReadFrequency, cutOff));
        values.x.addFilter(new ButterworthLP<int16_t>(dataReadFrequency, cutOff));
    }
    bool update(int16_t x, int16_t y, int16_t z) { values.updateAll(x, y, z); }
    bool update(Vector<int16_t> vect) { values.updateAll(vect.x, vect.y, vect.z); }
    bool dataReady() { return timer.IsReady(); }
    virtual String toString()
    {
        return "Point3D(" +
               values.x.toString() + ", " +
               values.y.toString() + ", " +
               values.z.toString() + ")";
    }
};

#endif