#pragma once
#ifndef DEBUG_H
#define DEBUG_H

#include "../../infac/DebugItem.h"
#include "../../structures/List.h"
#include "../Output/Output.h"

class Debug {
private:
    long long int counter=0;
    long unsigned int prevTime;
public:
    List<DebugItem*> items;
    Debug();
    void Show();
    void CalculateFreq();
};

#include "Debug.cpp"

#endif