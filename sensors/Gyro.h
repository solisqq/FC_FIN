#pragma once
#ifndef IMU_H
#define IMU_H

#include <String>
#include "MPU9250.h"
#include "../infac/Printable.h"
#include "../infac/Sensor3D.h"

SPIClass *MPUSPI;
MPU9250 *mpu;

class Gyro : public Sensor3D {
public:
    Gyro() {}
    void Init() {
        Connect();
    }
    void Connect() {
		MPUSPI = new SPIClass();
		MPUSPI->begin(MPU_SCK,MPU_MOSI,MPU_MISO);
		mpu = new MPU9250(*MPUSPI, MPU_CS);
		
		if(!mpu->begin()) _CriticalError(output, "IMU");
	}
    void SetDefault() {
		//GYRO 8800Hz, No DLPF
	  	mpu->writeRegister(mpu->CONFIG, 0x00);
	  	mpu->writeRegister(mpu->GYRO_CONFIG, 0x00);
	  	//100HZ 16bits
	  	
	  	//ACCEL 4G range
	  	mpu->setAccelRange(MPU9250::AccelRange::ACCEL_RANGE_4G);
	  	//Accel 1046Hz No DLPF
	  	mpu->writeRegister(mpu->ACCEL_CONFIG2, 0x00);

	  	//Init 
		gyro.Init(IMU_FREQ, GYRO_LP);
		baro.Init(MPUSPI, BARO_FREQ);
		mag.Init(MAG_FREQ, MAG_LP);
		distanceSensor.Init(TRIG_PIN,ECHO_PIN, 1.0);
		mpu->readRaw(&accel.values, &gyro.values, &temperature);
		mag.CalibrateScale();
	}
};

#endif