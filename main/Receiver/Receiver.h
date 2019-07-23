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
#include "../../filters/Mapper.h"
#include "../../filters/ExpHighPass.h"
#include "../../filters/Exponential.h"
#include "Axis.h"
#include "PPMHandler.h"

class Receiver : public AllowPrint, public DebugItem {
public:
    Axis **Channels;
    Axis Throttle,Roll,Pitch,Yaw;
    Axis Switch[4];
    void initialize(int RTX_PIN, int medianStr, float irStr);
    void update();
    virtual String getClassName();
    virtual String getDebugMsg(bool raw=false);
    virtual String toString();
    Point3D<float> getPoint3D();
    bool isActive();
private:
    bool isRadioOn();
    void errorNoRadio();
};

#include "Receiver.cpp"

#endif