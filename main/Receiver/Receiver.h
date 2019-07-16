#pragma once
#ifndef RECEIVER_H
#define RECEIVER_H

#include "../../infac/DebugItem.h"
#include "../../structures/List.h"
#include "../../utilities/Output/Output.h"
#include "../../infac/AllowPrint.h"
#include "../../infac/FilterableValue.h"
#include "../../filters/ClosesTo.h"
#include "../../filters/SimpleIR.h"
#include "Axis.h"

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
        channel_length[CPPM_Pointer] = CPPM_Pulse;
        bitSet(CPPM_FLAGS, CPPM_Pointer);      
        CPPM_Pointer++;
    }
    else CPPM_Pointer = 0;
}

class Receiver : public AllowPrint, public DebugItem {
public:
    Axis **Channels;
    Axis Throttle,Roll,Pitch,Yaw;
    Axis Switch[4];
    void initialize(int RTX_PIN, int medianStr, float irStr) {
        Channels = new Axis*[8];

        Channels[0] = &Throttle;
        Channels[1] = &Roll;
        Channels[2] = &Pitch;
        Channels[3] = &Yaw;

        for(int i=4, j=0; i<8; i++,j++){ 
            Channels[j]->addFilter(new ClosesTo<float>(medianStr, 3000.0));
            Channels[j]->addFilter(new SimpleIR<float>(irStr));
            Channels[i] = &Switch[j];
            Switch[j].addFilter(new ClosesTo<float>(3, 3000.0));
        }

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
        msg+= Throttle.toString()+Output::coma;
        return msg;
    }
};

#include "Receiver.cpp"

#endif