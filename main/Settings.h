#pragma once
#ifndef SETTINGS_FC_H
#define SETTINGS_FC_H

#include "../math/Point3D/Vector.h"

class Settings
{
public:
    class Gyro
    {
    public:
        static int freq;
        static int calibThreshold;
        static float cutOff;
        static float sensitivity;
        static double dt;
    };
    class Accel
    {
    public:
        static int freq;
        static float cutOff;
        static float range;
        static int16_t oneGAsInt;
        static int16_t xOffset;
        static int16_t yOffset;
    };
    class RX
    {
    public:
        static bool stopOnFail;
        static float threshold;
        static float yawDivider;
    };
    class PID
    {
    public:
        static int freq;
        static float dt;
        static Vector<float> P;
        static Vector<float> I;
        static Vector<float> D;
        static Vector<float> DFilter;
        
    };
    class Math
    {
    public:
        static float constPI;
    };
    class IMU {
        public:
        static float gyroStr;
    };
    class Engines {
        public:
        static int minimum;
        static int start;
        static int maximum;
        static int fl;
        static int fr;
        static int br;
        static int bl;
    };
};

float Settings::Gyro::cutOff = 70.0;
int Settings::Gyro::freq = 8000;
int Settings::Gyro::calibThreshold = 100;
float Settings::Gyro::sensitivity = 120.0;

float Settings::Accel::cutOff = 4.0;
int Settings::Accel::freq = 1000;
float Settings::Accel::range = 4.0;
int16_t Settings::Accel::oneGAsInt = 8192;
int16_t Settings::Accel::xOffset = 0;
int16_t Settings::Accel::yOffset = 0;

bool Settings::RX::stopOnFail = false;
float Settings::RX::threshold = 0.4;
float Settings::RX::yawDivider = 4;

int Settings::PID::freq = 300;
float Settings::PID::dt = 1.0/Settings::PID::freq;
//----------------------------------------------R----P-----Y----
Vector<float> Settings::PID::P = Vector<float>(0.0, 0.0, 0.0);
Vector<float> Settings::PID::I = Vector<float>(0.0, 0.0, 0.0);
Vector<float> Settings::PID::D = Vector<float>(1.0, 1.0, 1.0);
Vector<float> Settings::PID::DFilter = Vector<float>(100, 100, 150);

float Settings::Math::constPI = 3.14159265358979323846;

float Settings::IMU::gyroStr = 0.9996;

int Settings::Engines::minimum = 1148;
int Settings::Engines::maximum = 1832;
int Settings::Engines::start = 1148;
int Settings::Engines::fl = 26; //27
int Settings::Engines::fr = 27; //14
int Settings::Engines::bl = 14; //26
int Settings::Engines::br = 25; //25


#endif