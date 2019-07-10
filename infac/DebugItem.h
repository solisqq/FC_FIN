#pragma once
#ifndef DEBUGITEM_H
#define DEBUGITEM_H

class DebugItem {
protected:
    virtual String getClassName() = 0;
public:
    virtual String getDebugMsg(bool raw=false) = 0; 
};

#endif