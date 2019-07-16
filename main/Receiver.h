#pragma once
#ifndef RECEIVER_H
#define RECEIVER_H

#include "../infac/DebugItem.h"
#include "../structures/List.h"
#include "../utilities/Output/Output.h"
#include "../infac/AllowPrint.h"
#include "../infac/FilterableValue.h"
#include "../filters/Median.h"
#include "../filters/SimpleIR.h"

byte CPPM_FLAGS = 0;
volatile int channel_length[8] = {0,0,0,0,0,0,0,0};

unsigned long CPPM_TimePrevious = 0;

void CPPM_ISR()
{
    byte static CPPM_Pointer = 0;
	unsigned long CPPM_TimeNow = micros();
	int CPPM_Pulse = int(CPPM_TimeNow - CPPM_TimePrevious); 
    CPPM_TimePrevious = CPPM_TimeNow;

    if(CPPM_Pulse < 2200)  
    {
        CPPM_Pointer &= B00000111; 
        channel_length = CPPM_Pulse;
        bitSet(CPPM_FLAGS, CPPM_Pointer);      
        CPPM_Pointer++;
    }
    else CPPM_Pointer = 0;
}

class Receiver : public AllowPrint, public DebugItem {
public:
    FilterableValue<int> Throttle;

    void initialize(int RTX_PIN) {
        Throttle.addFilter(new Median<int>(3, 1000));
        pinMode(21, INPUT);
      	attachInterrupt(digitalPinToInterrupt(21), CPPM_ISR, RISING);
    }
    void update() {
        Throttle.update(channel_length[0]);
    }
    virtual String getClassName() {
        return "Receiver";
    }
    virtual String getDebugMsg(bool raw=false) {
        return toString();
    }
    virtual String toString() {
        String msg="RX: ";
        for(int i=0; i<8; i++) 
            msg+= channel_length[i].value+Output::coma;
        return msg;
    }
};

#include "Receiver.cpp"

#endif