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
#include "../filters/Mapper.h"
#include "../utilities/Timer/DeltaTime.h"

class IMU : public DebugItem
{
private:
	Debug *debug;
	MPU9250 *mpu;
	FilterableValue<float> compStrX;
	FilterableValue<float> compStrY;
	DeltaTime deltaT;

public:
	SPIClass *cSPI;
	bool dataReady = false;
	Gyro gyro;
	Accel accel;
	Point3D<float> eulers;
	Vector<float> gyroEulers;

	IMU() {}
	bool initialize(short int MPU_SCK, short int MPU_MOSI, short int MPU_MISO, short int MPU_CS, Debug *dbg = nullptr)
	{
		if (!connect(MPU_SCK, MPU_MOSI, MPU_MISO, MPU_CS))
			return false;
		debug = dbg;
		setDefault();

		gyro.initialize(Settings::Gyro::freq);
		accel.initialize(Settings::Accel::freq);

		//calibrating gyro sensor and accelerometer Z val
		this->calibrate(Settings::IMU::calibTime, Settings::Gyro::freq / 10);

		//Settings up butterworth low pass filter
		gyro.setLowPassFilter(Settings::Gyro::cutOff);
		accel.setLowPassFilter(Settings::Accel::cutOff);

		//Setting up rational filter
		compStrX.addFilter(new Mapper<float>(16384, -16384, -0.010, 0.010));
		compStrY.addFilter(new Mapper<float>(16384, -16384, -0.010, 0.010));
		compStrX.addFilter(new SimpleIR<float>(0.85));
		compStrY.addFilter(new SimpleIR<float>(0.85));

		//Initializing eulers' angles with accelerometer data
		for (int i = 0; i < Settings::Accel::freq; i++)
		{
			while (!accel.dataReady())
			{
			}
			accel.updateByMPU(mpu);
		}
		Vector<float> accelData = accel.getEulers(eulers);
		eulers.z.value = 0;
		eulers.y.value = accelData.y;
		eulers.x.value = accelData.x;
		gyroEulers = eulers.getVector();
		return true;
	}
	void update()
	{
		if (mpu->isDataReady())
		{
			gyro.updateByMPU(mpu);
			//debug->CalculateFreq();
		}
		if (accel.dataReady())
		{
			accel.updateByMPU(mpu);
			sensorFusion();
		}
	}

private:
	void sensorFusion()
	{
		//calculating delta time
		double dt = Settings::PID::dt;
		if (deltaT.isSet()) dt = deltaT.calcInMS();

		//Getting processed data from gyro and accel
		Vector<float> gyroData = gyro.getDegPerSec();
		Vector<float> accelData = accel.getEulers(eulers);

		//Rational filtering accelerometer strength in complementary
		compStrX.update(gyro.values.x.value);
		compStrY.update(gyro.values.y.value);
		float compStrX_converted = Settings::IMU::gyroStr + abs(compStrX.value);
		float compStrY_converted = Settings::IMU::gyroStr + abs(compStrY.value);
		if (compStrX_converted > 1.0)
			compStrX_converted = 1.0;
		if (compStrY_converted > 1.0)
			compStrY_converted = 1.0;

		//Settings up offsets
		accelData.x = accelData.x + Settings::Accel::xOffset;
		accelData.y = accelData.y + Settings::Accel::yOffset;

		gyroData *= dt;
		gyroEulers = gyroEulers + gyroData;
		gyroData.x += eulers.x.value;
		gyroData.y += eulers.y.value;
		eulers.x.value = (gyroData.x * compStrX_converted) + (accelData.x * (1.0 - compStrX_converted));
		eulers.y.value = (gyroData.y * compStrY_converted) + (accelData.y * (1.0 - compStrY_converted));
		eulers.z.value += gyroData.z;
		gyroEulers = gyroEulers*0.9 + eulers.getVector()*0.1;
		dataReady = true;
	}
	bool connect(short int MPU_SCK, short int MPU_MOSI, short int MPU_MISO, short int MPU_CS)
	{
		cSPI = new SPIClass();
		cSPI->begin(MPU_SCK, MPU_MOSI, MPU_MISO);
		cSPI->setFrequency(20000000);
		cSPI->setClockDivider(SPI_CLOCK_DIV2);
		mpu = new MPU9250(*cSPI, MPU_CS);
		if (mpu->begin() == 1)
			return true;
		else
			return false;
	}
	virtual String getDebugMsg(bool raw)
	{
		String msg = getClassName() + ": ";
		msg += gyroEulers.toString();
		return msg;
	}
	void setDefault()
	{
		//GYRO 8800Hz, No DLPF
		mpu->writeRegister(mpu->CONFIG, 0x00);
		mpu->writeRegister(mpu->GYRO_CONFIG, 0x00);
		mpu->enableDataReadyInterrupt();
		//100HZ 16bits

		//ACCEL 4G range
		mpu->setAccelRange(MPU9250::AccelRange::ACCEL_RANGE_4G);
		//Accel 1046Hz No DLPF
		mpu->writeRegister(mpu->ACCEL_CONFIG2, 0x00);
	}
	void calibrate(unsigned int n1, unsigned int n2)
	{
		Output::info("Calibrating IMU...");
		int *avgVal[3];
		int *avgValLow[4];
		int16_t offsets[4];
		for (int i = 0; i < 3; i++)
		{
			avgVal[i] = new int[n2];
			avgValLow[i] = new int[n1];
		}
		avgValLow[3] = new int[n1];
		Vector<int16_t> gyroData;
		Vector<int16_t> accelData;
		for (int j = 0; j < n1; j++)
		{
			for (int i = 0; i < n2; i++)
			{
				while (!gyro.dataReady())
				{
				}
				mpu->readRawGyro(&gyroData);
				avgVal[0][i] = static_cast<int>(gyroData.x);
				avgVal[1][i] = static_cast<int>(gyroData.y);
				avgVal[2][i] = static_cast<int>(gyroData.z);
				if (i > 0)
				{
					if (isInMotion(avgVal[0][i], avgVal[0][i - 1], avgVal[1][i], avgVal[1][i - 1], avgVal[2][i], avgVal[2][i - 1], Settings::Gyro::calibThreshold))
					{
						Output::throwExc(Exception(Exception::Type::Warning, getClassName(), "calibration failed. Trying again..."));
						delay(1000);
						calibrate(Settings::IMU::calibTime, Settings::Gyro::freq / 10);
						return;
					}
				}
			}
			mpu->readRawAccel(&accelData);
			avgValLow[0][j] = Algorithms<int>::calcAvg(avgVal[0], n2);
			avgValLow[1][j] = Algorithms<int>::calcAvg(avgVal[1], n2);
			avgValLow[2][j] = Algorithms<int>::calcAvg(avgVal[2], n2);
			avgValLow[3][j] = static_cast<int>(accelData.z);
		}
		offsets[0] = static_cast<int16_t>(Algorithms<int>::calcAvg(avgValLow[0], n1));
		offsets[1] = static_cast<int16_t>(Algorithms<int>::calcAvg(avgValLow[1], n1));
		offsets[2] = static_cast<int16_t>(Algorithms<int>::calcAvg(avgValLow[2], n1));
		offsets[3] = static_cast<int16_t>(Algorithms<int>::calcAvg(avgValLow[3], n1));

		Vector<float> gyroValues = Vector<float>(0.0f);
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 750; j++)
			{
				while (!gyro.dataReady()){}
				mpu->readRawGyro(&gyroData);
				if(abs(gyroData.x-offsets[0])>Settings::Gyro::calibThreshold*3 || abs(gyroData.y-offsets[1])>Settings::Gyro::calibThreshold*3 || abs(gyroData.z-offsets[2])>Settings::Gyro::calibThreshold*3) {
					Output::throwExc(Exception(Exception::Type::Warning, getClassName(), "calibration failed. Trying again..."));
					delay(1000);
					calibrate(Settings::IMU::calibTime, Settings::Gyro::freq / 10);
					return;
				}
				gyroValues.x += ((gyroData.x-offsets[0])/200);
				gyroValues.y += ((gyroData.y-offsets[1])/200);
				gyroValues.z += ((gyroData.z-offsets[2])/200);
			}
			offsets[0] -= gyroValues.x;
			offsets[1] -= gyroValues.y;
			offsets[2] -= gyroValues.z;
			gyroValues = Vector<float>(0.0f);
		}

		gyro.values.x.addFilter(new Offset<int16_t>(offsets[0]-2));
		gyro.values.y.addFilter(new Offset<int16_t>(offsets[1]-5));
		gyro.values.z.addFilter(new Offset<int16_t>(offsets[2]));
		accel.values.z.addFilter(new Offset<int16_t>(offsets[3] - Settings::Accel::oneGAsInt));
		Output::info("Calibrating done!");
	}
	bool isInMotion(int cx, int px, int cy, int py, int cz, int pz, int threshold)
	{
		return (cx > px + threshold || cx < px - threshold || cy > py + threshold || cy < py - threshold || cz > pz + threshold || cz < pz - threshold);
	}

protected:
	virtual String getClassName()
	{
		return "IMU";
	}
};

#endif