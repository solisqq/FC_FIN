#ifndef DELTATIME_H
#define DELTATIME_H

#include <Arduino.h>

class DeltaTime {
public:
	unsigned long micros_time=0;
	DeltaTime(){}
	bool isSet() {
		if(micros_time==0) {micros_time = micros();return false;}
		return true;
	}
	unsigned long calc() {
		unsigned long toRet = micros() - micros_time;
		micros_time = micros();
		return toRet;
	}
	double calcInMS() {return 1.0/calc();}
};

#endif