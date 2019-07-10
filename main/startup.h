#pragma once
#include "../utilities/Debug/Debug.h"
#include "globalObjects.h"
#include "../filters/SimpleIR.h"
#include "../math/Point3D/Point3D.h"
#include "../utilities/Timer/Timer.h"

Debug debugger;

Timer debugTimer;
Point3D<int> somePoint;
long randNumberX;
long randNumberY;
long randNumberZ;

void initialize(){
	Output::initialize();
	delay(10);
	Serial.println("cs");
	somePoint.x.addFilter(new SimpleIR<int>(0.98));
	somePoint.y.addFilter(new SimpleIR<int>(0.9));
	somePoint.z.addFilter(new SimpleIR<int>(0.85));
	randomSeed(analogRead(0));
	debugTimer.Init(30);
}
