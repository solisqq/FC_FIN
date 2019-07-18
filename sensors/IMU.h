#pragma once
#ifndef IMU_H
#define IMU_H

#include <String>
#include "MPU9250.h"
#include "Gyro/Gyro.h"


class IMU {
private:
    SPIClass *MPUSPI;
    MPU9250 *mpu;
public:
    Gyro gyro;  
    IMU(){}
    bool initialize(short int MPU_SCK, short int MPU_MOSI, short int MPU_MISO, short int MPU_CS) {
        if(!connect(MPU_SCK, MPU_MOSI, MPU_MISO, MPU_CS)) return false;
        setDefault();
        return true;
    }
	void update() {
		Vector<int16_t> gyroData;
		mpu->readRawGyro(&gyroData);
		gyro.update(gyroData);
	}
private:
    bool connect(short int MPU_SCK, short int MPU_MOSI, short int MPU_MISO, short int MPU_CS) {
		MPUSPI = new SPIClass();
		MPUSPI->begin(MPU_SCK,MPU_MOSI,MPU_MISO);
		mpu = new MPU9250(*MPUSPI, MPU_CS);
		if(!mpu->begin()) return false;
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

		//gyro.initialize();
	}
	
};

#endif