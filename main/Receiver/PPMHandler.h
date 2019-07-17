#pragma once
#ifndef PPMHANDLER_H
#define PPMHANDLER_H

byte CPPM_FLAGS = 0;
volatile int channel_length[8] = {0,0,0,0,0,0,0,0};
unsigned long CPPM_TimePrevious = 0;
volatile bool inactive = true;
int errorsCount = 0;

void CPPM_ISR()
{
    inactive = false;
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
    else {
        CPPM_Pointer = 0;
    }
}

#endif