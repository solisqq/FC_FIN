#pragma once
#ifndef COMMANDS_H
#define COMMANDS_H

#include "../../infac/Action.h"
#include "../Debug/Debug.h"
#include "../Output/Output.h"

class DebugAddAction : public Action {
    DebugItem &item;
    Debug debug;
public:
    DebugAddAction(Debug& _debugger, DebugItem& _item): item(_item), debug(_debugger){}
    virtual void execute(int *params) {
        debug.items.pushBack(&item);
    }
};

#endif