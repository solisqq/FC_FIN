#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../../math/Point3D/Point3D.h"
#include "../Receiver/Receiver.h"
class Controller
{
private:
    Point3D<float> point;
public:
    Controller();
    ~Controller();
};

Controller::Controller(/* args */)
{
}

Controller::~Controller()
{
}

#endif CONTROLLER_H