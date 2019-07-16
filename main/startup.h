#pragma once
#include "../utilities/Debug/Debug.h"
#include "globalObjects.h"
#include "../filters/SimpleIR.h"
#include "../math/Point3D/Point3D.h"
#include "../utilities/Timer/Timer.h"
#include "../utilities/CommandSystem/CommandSystem.h"
#include "Receiver/Receiver.h"

Debug debugger;

Timer debugTimer;
Timer rxTimer;

Receiver rx;
CommandSystem cmd;

void initialize(){
	Output::initialize();
	delay(10);
	Serial.println("cs");
	debugTimer.Init(30);
	rxTimer.Init(20);
	rx.initialize(21, 7, 0.8);
	cmd.setDebugOnCMD(debugger, rx, "receiver");
}

