#pragma once
#ifndef IMU_H
#define IMU_H

#include <String>
#include "MPU9250.h"
#include "Gyro/Gyro.h"
#include "../algorithms/algorithms.h"
#include "../filters/Offset.h"
#include "../filters/ButterworthLP.h"
#include "../main/Settings.h"
#include "../utilities/Timer/Timer.h"
#include "../infac/DebugItem.h"
#include "../infac/Pair.h"
#include "../filters/Complementary.h"
#include "Accel/Accel.h"

class IMU : public DebugItem {
private:
    SPIClass *MPUSPI;
    MPU9250 *mpu;
	Timer pidTimer;
public:
	bool dataReady=false;
    Gyro gyro; 
	Accel accel;
	//Point3D<float> eulers; 
    IMU(){}
    bool initialize(short int MPU_SCK, short int MPU_MOSI, short int MPU_MISO, short int MPU_CS) {
		if(!connect(MPU_SCK, MPU_MOSI, MPU_MISO, MPU_CS)) return false;

        setDefault();

		gyro.initialize(Settings::Gyro::freq);
		accel.initialize(Settings::Accel::freq);

		this->calibrate(100,Settings::Gyro::freq/10);

		gyro.setLowPassFilter(Settings::Gyro::cutOff);
		gyro.setAvgFilter(Settings::Gyro::freq/Settings::PID::freq);
		accel.setLowPassFilter(Settings::Accel::cutOff);

		pidTimer.Init(1000000 / Settings::PID::freq, true);
		//eulers.x.addFilter(new Complementary(0.98));
		return true;
    }
	void update() {
		if(gyro.dataReady()) {
			Vector<int16_t> gyroData;
			mpu->readRawGyro(&gyroData);
			gyro.update(gyroData);
		}
		if(accel.dataReady()) {
			Vector<int16_t> accelData;
			mpu->readRawAccel(&accelData);
			accel.update(accelData);
		}
		/* if(pidTimer.dataReady()) {
			eulers.x.update(Pair<float, float>(static_cast<float>(gyro.x.value), gyro.x.value));
		}*/
	}
private:
    bool connect(short int MPU_SCK, short int MPU_MOSI, short int MPU_MISO, short int MPU_CS) {
		MPUSPI = new SPIClass();
		MPUSPI->begin(MPU_SCK,MPU_MOSI,MPU_MISO);
		mpu = new MPU9250(*MPUSPI, MPU_CS);
		if(mpu->begin()==1) return true;
		else return false;
	}
	virtual String getDebugMsg(bool raw=false) {
		String msg = getClassName()+": ";
		//msg+=eulers.toString();
	}
    void setDefault() {
		//GYRO 8800Hz, No DLPF
	  	mpu->writeRegister(mpu->CONFIG, 0x00);
	  	mpu->writeRegister(mpu->GYRO_CONFIG, 0x00);
	  	//100HZ 16bits
	  	
	  	//ACCEL 4G range
	  	mpu->setAccelRange(MPU9250::AccelRange::ACCEL_RANGE_4G);
	  	//Accel 1046Hz No DLPF
	  	mpu->writeRegister(mpu->ACCEL_CONFIG2, 0x00);
	}
	void calibrate(unsigned int n1, unsigned int n2) {
		Output::info("Calibrating IMU...");
		int *avgVal[3];
		int *avgValLow[3];
		for(int i=0; i<3; i++) {
			avgVal[i] = new int[n2];
			avgValLow[i] = new int[n1];
		}
		int16_t offsets[3];
		for(int j=0; j<n1; j++) {
			for(int i=0; i<n2; i++) {
				while(!gyro.dataReady()) {}
				Vector<int16_t> gyroData;
				mpu->readRawGyro(&gyroData);
				avgVal[0][i] = static_cast<int>(gyroData.x);
				avgVal[1][i] = static_cast<int>(gyroData.y);
				avgVal[2][i] = static_cast<int>(gyroData.z);
			}
			avgValLow[0][j] = Algorithms<int>::calcAvg(avgVal[0], n2);
			avgValLow[1][j] = Algorithms<int>::calcAvg(avgVal[1], n2);
			avgValLow[2][j] = Algorithms<int>::calcAvg(avgVal[2], n2);
		}
		offsets[0] = static_cast<int16_t>(Algorithms<int>::calcAvg(avgValLow[0], n1));
		offsets[1] = static_cast<int16_t>(Algorithms<int>::calcAvg(avgValLow[1], n1));
		offsets[2] = static_cast<int16_t>(Algorithms<int>::calcAvg(avgValLow[2], n1));
		gyro.values.x.addFilter(new Offset<int16_t>(offsets[0]));
		gyro.values.y.addFilter(new Offset<int16_t>(offsets[1]));
		gyro.values.z.addFilter(new Offset<int16_t>(offsets[2]));
		Output::info("Calibrating done!");
	}
protected:
	virtual String getClassName() {
		return "IMU";
	}
};

#endif