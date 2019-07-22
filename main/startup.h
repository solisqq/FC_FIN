#pragma once
#include "globalObjects.h"

String command;

void initialize(){
	Output::initialize();
	Output::info("Welcome to HawkFC! Have fun flight!");
	Output::info("Initializing HawkFC components...");

	debugTimer.Init(10);
	rxTimer.Init(20);

	if(!imu.initialize(18,19,23,22)) {
		Output::throwExc(Exception(Exception::Type::Critical, "IMU", "Can't connect"));
		WAIT_LONG;
		ESP.restart();
	}
	Output::info("IMU initialized properly.");
	rx.initialize(21, 7, 0.8);
	if(!rx.isActive() && Settings::RX::stopOnFail) {
		Exception rxFail = Exception(Exception::Type::Error, "RX", "No signal");
		Output::throwExc(rxFail);
		EXCEPTION_HOLD(rx.isActive(),rxFail);
	}
	cmd.setDebugOnCMD(debugger, rx, "rx");
	cmd.setDebugOnCMD(debugger, imu.gyro, "gyro");
	cmd.setDebugOnCMD(debugger, imu.accel, "accel");
	cmd.setDebugOnCMD(debugger, imu, "imu");
}

