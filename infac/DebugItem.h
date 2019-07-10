#pragma once
#ifndef DEBUGITEM_H
#define DEBUGITEM_H

class DebugItem {
private:
    bool state;
public:
    void debugOn() { state = true; } 
    void debugOff() { state = false; } 
    void switchState() { state = !state; } 
    virtual String getDebugMsg(bool raw=false) = 0;
};

#endif