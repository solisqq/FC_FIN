#pragma once
#ifndef PIDF_H
#define PIDF_H

#include "../math/Point3D/Point3D.h"
#include "../math/Point3D/Vector.h"
#include "Settings.h"
#include "../infac/DebugItem.h"
#include "../utilities/Output/Output.h"
#include "../utilities/Timer/DeltaTime.h"
#include "../filters/SimpleIR.h"
#include "../filters/ButterworthLP.h"
#include "../filters/MovAverage.h"

class PID : public DebugItem
{
private:
    Vector<float> preError;
    DeltaTime deltaT;
public:
    Point3D<float> values;
    Point3D<float> proportional;
    Vector<float> integral;
    Point3D<float> derivative;
    
    PID(/* args */) {
        //proportional.x.addFilter(new ButterworthLP<float>(Settings::PID::freq, Settings::PID::PFilter));
        //proportional.y.addFilter(new ButterworthLP<float>(Settings::PID::freq, Settings::PID::PFilter));
        //proportional.z.addFilter(new ButterworthLP<float>(Settings::PID::freq, Settings::PID::PFilter));
        derivative.x.addFilter(new ButterworthLP<float>(Settings::PID::freq, Settings::PID::DFilter));
        derivative.y.addFilter(new ButterworthLP<float>(Settings::PID::freq, Settings::PID::DFilter));
        derivative.z.addFilter(new ButterworthLP<float>(Settings::PID::freq, Settings::PID::DFilter));
    }
    Point3D<float> run(Vector<float> current, Point3D<float> desired) {
        double dt = Settings::PID::dt;
        if(deltaT.isSet()) dt = deltaT.calcInMS();
        
        Vector<float> error;
        error = desired.getVector() - current;
        
        proportional.updateAll(error*Settings::PID::P);
        integral = integral + ((error*dt)*Settings::PID::I);
        derivative.updateAll(((error-preError)/dt)*Settings::PID::D);
        
        preError = error;

        values.x.update(proportional.x.value + integral.x + derivative.x.value);
        values.y.update(proportional.y.value + integral.y + derivative.y.value);
        values.z.update(proportional.z.value + integral.z + derivative.z.value);
        return values;
    }
    void reset() {
        proportional.resetVals();
        integral.resetVals();
        derivative.resetVals();
        values.resetVals();
    }
    //Point3D<float> run(Point3D<float> current, Point3D<float> desired) {return run(current.getVector(), desired);}
    virtual String getClassName() {return "PID";}
    virtual String getDebugMsg(bool raw=false) {
        String msg = getClassName()+": " + values.toString();
        return msg;
    }
};

#endif