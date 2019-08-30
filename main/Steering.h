#pragma once
#ifndef STEERING_H
#define STEERING_H

#include "Engine.h"
#include "../infac/DebugItem.h"
#include "PID.h"
#include "../utilities/Debug/Debug.h"
#include "../math/Point3D/Vector.h"
class Steering : public DebugItem
{
public:
    enum State {
        Idle = 0,
        Flying = 1,
        Setup = 2,
        Calibrate = 3
    };
    PID pid;
    State currentState = State::Idle;
private:
    Engine frontLeft;
    Engine frontRight;
    Engine backLeft;
    Engine backRight;
    Engine **engines;
    
    Receiver *_rx;
    IMU *_imu;
    PID *_pid;
    Debug *_debug;

    Vector<float> accumulatedEulers;
    int accumulationCounter=0;
    
public:
    Steering() {
        engines = new Engine*[4];
        engines[0] = &frontLeft;
        engines[1] = &frontRight;
        engines[2] = &backLeft;
        engines[3] = &backRight;
    }
    void init(IMU *_imu1, Receiver *_rx1, PID *_pid1, Debug *_debug1) {
        _imu = _imu1;
        _rx = _rx1;
        _pid = _pid1;
        _debug = _debug1;
        frontLeft.Init(Settings::Engines::fl);
        frontRight.Init(Settings::Engines::fr);
        backLeft.Init(Settings::Engines::bl);
        backRight.Init(Settings::Engines::br);

        delay(200);
    }
    void setState(State state) {
        currentState = state;
        if(currentState==State::Idle) {
            stop();
            _pid->reset();
        }
        else if(currentState==State::Flying) 
            setThrottle();
    }
    void setThrottle() {
        if(currentState==State::Flying) {
            Vector<float> pidV = (_pid->run(_imu->gyroEulers, _rx->getPoint3D())).getVector();
            frontLeft.SetSpeed(max(_rx->Throttle.get() - pidV.y + pidV.x + pidV.z, Settings::Engines::start));
            frontRight.SetSpeed(max(_rx->Throttle.get() - pidV.y - pidV.x - pidV.z, Settings::Engines::start));
            backLeft.SetSpeed(max(_rx->Throttle.get() + pidV.y + pidV.x - pidV.z, Settings::Engines::start));
            backRight.SetSpeed(max(_rx->Throttle.get() + pidV.y - pidV.x + pidV.z, Settings::Engines::start));
            accumulationCounter=1;
        } else stop();
    }
    void calibrate() {
        Output::printLine("Calibrating ESCs...");
        delay(2000);
        for(int i=0; i<4; i++)
            engines[i]->SetSpeed(Settings::Engines::maximum);
        delay(6000);
        for(int i=0; i<4; i++)
            engines[i]->SetSpeed(Settings::Engines::minimum);
        delay(4000);
    }
    void stop() {
        for(int i=0; i<4; i++)
            engines[i]->SetSpeed(Settings::Engines::minimum);
    }
    void test() {
        delay(3000);
        frontLeft.SetSpeed(1400);
        delay(3000);
        frontLeft.SetSpeed(1148);
        frontRight.SetSpeed(1400);
        delay(3000);
        frontRight.SetSpeed(1148);
        backLeft.SetSpeed(1400);
        delay(3000);
        backLeft.SetSpeed(1148);
        backRight.SetSpeed(1400);
        delay(3000);
        backRight.SetSpeed(1400);
    }
    virtual String getClassName() {
        return "Engines";
    }
    virtual String getDebugMsg(bool raw=false) {
        String msg = getClassName()+": ";
        for(int i=0; i<4; i++)
            msg+=engines[i]->toString()+" ";
        return msg;
    }
    private:
    int max(const float first, const int second) {
        if(first>second) return first;
        else return second;
    }
};

#endif