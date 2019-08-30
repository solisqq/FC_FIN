#pragma once
#ifndef COMMANDS_H
#define COMMANDS_H

#include "../../infac/Action.h"
#include "../Debug/Debug.h"
#include "../Output/Output.h"
#include "../SDCard/SDCard.h"

class DebugAddAction : public Action {
    DebugItem &item;
    Debug &debug;
public:
    DebugAddAction(Debug& _debugger, DebugItem& _item): item(_item), debug(_debugger){}
    virtual void execute(List<String> &params) {
        debug.items.pushBack(&item);
    }
};

class DebugClear : public Action {
    Debug &debug;
public:
    DebugClear(Debug& _debugger): debug(_debugger){}
    virtual void execute(List<String> &params) {
        debug.items.clear();
    }
};

class CMDSet : public Action {
    Vector<float> *vectf;
    String *str;
    float *flt;
    int *integer;
    double *dbl;
    SDCard *memory;
    SPIClass *cSPI;
public:
    enum Type {vecttf,strr,fltt,intt,dbll};
    Type type;
    CMDSet(SDCard *_memory, SPIClass *_cSPI, Vector<float> *_bac): cSPI(_cSPI), memory(_memory), vectf(_bac), type(Type::vecttf) {}
    CMDSet(SDCard *_memory, SPIClass *_cSPI, String *_bac): cSPI(_cSPI), memory(_memory), str(_bac), type(Type::strr) {}
    CMDSet(SDCard *_memory, SPIClass *_cSPI, float *_bac): cSPI(_cSPI), memory(_memory), flt(_bac), type(Type::fltt) {}
    CMDSet(SDCard *_memory, SPIClass *_cSPI, int *_bac): cSPI(_cSPI), memory(_memory), integer(_bac), type(Type::intt) {}
    CMDSet(SDCard *_memory, SPIClass *_cSPI, double *_bac): cSPI(_cSPI), memory(_memory), dbl(_bac), type(Type::dbll) {}

    virtual void execute(List<String> &params) {
        if(params.Count<1) return;
        if(type==Type::vecttf) {
            if(params.Count<3) return;
            *vectf = Vector<float>(params.getAndPopFront().toFloat(),params.getAndPopFront().toFloat(),params.getAndPopFront().toFloat());
        } else if(type==Type::strr) {
            *str = params.front->val;
        } else if(type==Type::fltt) {
            *flt = params.front->val.toFloat();
        } else if(type==Type::intt) {
            *integer = params.front->val.toInt();
        } else if(type==Type::dbll) {
            *dbl = params.front->val.toDouble();
        }
        //memory->writeSettings(cSPI, Settings::getSettingsFileString());
    }
};

class CMDShow : public Action {
public:
    CMDShow() {}
    virtual void execute(List<String> &params) {
        if(params.Count<=0) return; 
        String item = params.front->val;
        if(item=="pid") Output::info(Settings::PID::toString());
        if(item=="offsets") Output::info((String)Settings::Accel::xOffset+", "+(String)Settings::Accel::yOffset);
    }
};

#endif