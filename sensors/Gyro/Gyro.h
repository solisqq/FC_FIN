#pragma once
#ifndef GYRO_H
#define GYRO_H

#include "../../infac/Sensor3D.h"
#include "../../filters/Average.h"

class Gyro : public Sensor3D, public DebugItem {
private:
    int accumulatedData[3];
    int counter=0;
public:
    Gyro() {}
    virtual String getClassName(){return "Gyro";}
    virtual String getDebugMsg(bool raw=false) {return Sensor3D::toString();}
    Vector<float> getDegPerSec() {
        Vector<float> converted = Vector<float>(
            (accumulatedData[0]/counter)/Settings::Gyro::sensitivity, 
            (accumulatedData[1]/counter)/Settings::Gyro::sensitivity, 
            (accumulatedData[2]/counter)/Settings::Gyro::sensitivity
        );
        counter = 0;
        return converted;
    }
    void setAvgFilter(int count) {
        Sensor3D::values.x.addFilter(new Average<int16_t>(count));
        Sensor3D::values.y.addFilter(new Average<int16_t>(count));
        Sensor3D::values.z.addFilter(new Average<int16_t>(count));
    }
    virtual void updateByMPU(MPU9250 *mpu) {
        Vector<int16_t> gyroData;
		mpu->readRawGyro(&gyroData);
        update(&gyroData);

        accumulatedData[0]+=values.x.value;
        accumulatedData[1]+=values.y.value;
        accumulatedData[2]+=values.z.value;
        counter++;
	}
};

#endif