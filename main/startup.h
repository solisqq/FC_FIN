#pragma once
#include "globalObjects.h"


void initialize(){
	Output::initialize();
	Output::info("Welcome to HawkFC! Have fun flight!");
	Output::info("Initializing HawkFC components...");

	debugTimer.Init(10);
	rxTimer.Init(20);
	inputTimer.Init(100);

	if(!imu.initialize(18,19,23,22,&debugger)) {
		Output::throwExc(Exception(Exception::Type::Critical, "IMU", "Can't connect"));
		WAIT_LONG;
		ESP.restart();
	}
	Output::info("IMU initialized properly.");
	rx.initialize(21, 7, Settings::RX::IRStr);
	//rx.initCheckRadio(); //UNCOMMENT IF NO !!!__!_TESTING
	cmd.setDebugClearOnCMD(debugger,"clear");
	cmd.setDebugOnCMD(debugger, imu.gyro, "gyro");
	cmd.setDebugOnCMD(debugger, rx, "rx");
	cmd.setDebugOnCMD(debugger, imu.accel, "accel");
	cmd.setDebugOnCMD(debugger, imu, "imu");
	cmd.setDebugOnCMD(debugger, pid, "pid");
	cmd.setDebugOnCMD(debugger, pid.proportional, "pid p");
	cmd.setDebugOnCMD(debugger, pid.integral, "pid i");
	cmd.setDebugOnCMD(debugger, pid.derivative, "pid d");
	cmd.setDebugOnCMD(debugger, copter, "engines");
	cmd.setShow("show");
	cmd.setSet(&mem, imu.cSPI, "setP", &Settings::PID::P);
	cmd.setSet(&mem, imu.cSPI, "setI", &Settings::PID::I);
	cmd.setSet(&mem, imu.cSPI, "setD", &Settings::PID::D);
	cmd.setSet(&mem, imu.cSPI, "setXO", &Settings::Accel::xOffset);
	cmd.setSet(&mem, imu.cSPI, "setYO", &Settings::Accel::yOffset);

	copter.init(&imu, &rx, &pid, &debugger);
	Settings::readFromFile(mem.readSettings(imu.cSPI));
	
}

