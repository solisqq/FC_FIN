#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

class Timer {
public:
	long long int millis_time=0;
	unsigned long micros_time=0;
	long long int toWait=0;
	Timer(bool precision=false);
	void Init();
	void Init(long long int time, bool precision=false);
	bool IsReady();
	void CalculateDifference(long long int *millis_time2);
	void CalculateDifference(unsigned long *micros_time2);
	void CalculateDifference(volatile unsigned long *micros_time2);
};

#include "Timer.cpp"

#endif