#pragma once
#ifndef DEBUG_H
#define DEBUG_H

#include "../../infac/DebugItem.h"
#include "../../structures/List.h"
#include "../Output/Output.h"

class Debug {
public:
    List<DebugItem*> items;
    Debug();
    void Show();
};

#include "Debug.cpp"

#endif