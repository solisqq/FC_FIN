#pragma once
#include "../utilities/Debug/Debug.h"
#include "globalObjects.h"
#include "../filters/SimpleIR.h"
#include "../math/Point3D/Point3D.h"
#include "../utilities/Timer/Timer.h"
#include "../utilities/CommandSystem/CommandSystem.h"
#include "Receiver/Receiver.h"
#include "../utilities/Exceptions/Exception.h"
#include "../sensors/IMU.h"

Debug debugger;
CommandSystem cmd;
List<Exception> exceptions;

Timer debugTimer;
Timer rxTimer;
Timer imuTimer;

IMU imu;
Receiver rx;

void initialize(){
	Output::initialize();
	delay(10);
	Serial.println("cs");

	debugTimer.Init(30);
	rxTimer.Init(20);
	imuTimer.Init(20);

	if(imu.initialize(18,19,23,22)) {
		Output::throwExc(Exception(Exception::Type::Critical, "IMU", "Can't connect"));
		delay(100);
		ESP.restart();
	}
	Output::info("IMU initialized properly.");
	rx.initialize(21, 7, 0.8);
	if(!rx.isActive()) {
		Exception rxFail = Exception(Exception::Type::Error, "RX", "No signal");
		Output::throwExc(rxFail);
		EXCEPTION_HOLD(rx.isActive(),rxFail);
	}
	//cmd.setDebugOnCMD(debugger, rx, "receiver");
	cmd.setDebugOnCMD(debugger, imu.gyro, "gyro");
}

