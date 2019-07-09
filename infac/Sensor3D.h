#pragma once
#ifndef SENSOR3D_H
#define SENSOR3D_H

#include "../math/Point3D/Point3D.h"
#include "../utilities/Timer.h"
#include "AllowPrint.h"

class Sensor3D: public AllowPrint {
public:
    Point3D<int> values;
protected:
    Point3D<int> offsets;
    int dataReadFrequency;
    Timer timer;

public:
    Sensor3D(){}
    void initialize(int frequency) {
        dataReadFrequency = frequency;
        timer.Init(1000000/frequency, true);
    }
    bool update(int x, int y, int z){values.updateAll(x,y,z);}
    bool update(Vector<Type> vect){values.updateAll(vect.x,vect.y,vect.z);}
    bool dataReady() {return timer.IsReady(); }
    virtual String toString() {
        return "Point3D("+
            values.x.toString()+", "+
            values.y.toString()+", "+
            values.z.toString()+")"
        ;
    }
};

#endif