#pragma once
#ifndef SETTINGS_FC_H
#define SETTINGS_FC_H

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
    };
    class PID
    {
    public:
        static int freq;
        static float dt;
        class RollPitch {
        public:
            static float P;
            static float I;
            static float D;
        };
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

int Settings::PID::freq = 1000;
float Settings::PID::dt = 0.001;

float Settings::PID::RollPitch::P = 4.0;
float Settings::PID::RollPitch::I = 0.2;
float Settings::PID::RollPitch::D = 1.5;

float Settings::Math::constPI = 3.14159265358979323846;

float Settings::IMU::gyroStr = 0.9996;

int Settings::Engines::minimum = 1148;
int Settings::Engines::maximum = 1832;
int Settings::Engines::start = 1200;
int Settings::Engines::fl = 27;
int Settings::Engines::fr = 14;
int Settings::Engines::bl = 26;
int Settings::Engines::br = 25;


#endif