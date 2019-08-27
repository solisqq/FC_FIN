#pragma once
#ifndef COMMANDS_H
#define COMMANDS_H

#include "../../infac/Action.h"
#include "../Debug/Debug.h"
#include "../Output/Output.h"

class DebugAddAction : public Action {
    DebugItem &item;
    Debug &debug;
public:
    DebugAddAction(Debug& _debugger, DebugItem& _item): item(_item), debug(_debugger){}
    virtual void execute(String *params) {
        debug.items.pushBack(&item);
    }
};

class DebugClear : public Action {
    Debug &debug;
public:
    DebugClear(Debug& _debugger): debug(_debugger){}
    virtual void execute(String *params) {
        debug.items.clear();
    }
};

template <class Type>
class CMDSet : public Action {
    Type *itemToSet;
public:
    CMDSet(Type *item):itemToSet(item) {}
    virtual void execute(String *params) {
        *itemToSet = params[0];
    }
};

#endif