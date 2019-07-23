#pragma once
#ifndef PIDF_H
#define PIDF_H

#include "../math/Point3D/Point3D.h"
#include "../math/Point3D/Vector.h"
#include "Settings.h"
#include "../infac/DebugItem.h"
#include "../utilities/Output/Output.h"

class PID : public DebugItem
{
private:
    Vector<float> preError;
public:
    Point3D<float> values;
    Point3D<float> proportional;
    Point3D<float> integral;
    Point3D<float> derivative;

    PID(/* args */) {}
    Point3D<float> run(Point3D<float> current, Point3D<float> desired) {
        Vector<float> error;
        error = desired.getVector() - current.getVector();
        
        proportional.updateAll(error*Settings::PID::RollPitch::P);
        integral.updateAll((error*Settings::PID::dt)*Settings::PID::RollPitch::I);
        derivative.updateAll((error-preError)/Settings::PID::dt);
        
        preError = error;

        values.x.update(proportional.x.value + integral.x.value + derivative.x.value);
        values.y.update(proportional.y.value + integral.y.value + derivative.y.value);
        values.z.update(proportional.z.value + integral.z.value + derivative.z.value);
        return values;
    }
    virtual String getClassName() {return "PID";}
    virtual String getDebugMsg(bool raw=false) {
        String msg = getClassName()+": " + values.toString();
        return msg;
    }
};

#endif