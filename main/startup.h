#pragma once
#include "../utilities/Debug/Debug.h"
#include "globalObjects.h"
#include "../filters/SimpleIR.h"
#include "../math/Point3D/Point3D.h"
#include "../utilities/Timer/Timer.h"
#include "../utilities/CommandSystem/CommandSystem.h"
#include "Receiver/Receiver.h"
#include "../utilities/Exceptions/Exception.h"

Debug debugger;

Timer debugTimer;
Timer rxTimer;

Receiver rx;
CommandSystem cmd;
List<Exception> exceptions;

void initialize(){
	Output::initialize();
	delay(10);
	Serial.println("cs");
	debugTimer.Init(30);
	rxTimer.Init(20);
	rx.initialize(21, 7, 0.8);
	if(!rx.isActive()) {
		Exception rxFail = Exception(Exception::Type::Critical, "RX", "No signal");
		Output::throwExc(rxFail);
		EXCEPTION_HOLD(rx.isActive(),rxFail);
	}
	cmd.setDebugOnCMD(debugger, rx, "receiver");
}

