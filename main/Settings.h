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
    };
    class Math
    {
    public:
        static float constPI;
    };
    class IMU {
        public:
        static float gyroStr;
        static float accelStr; 
    };
};

float Settings::Gyro::cutOff = 70.0;
int Settings::Gyro::freq = 8000;
int Settings::Gyro::calibThreshold = 50;
float Settings::Gyro::sensitivity = 125.0;

float Settings::Accel::cutOff = 8.0;
int Settings::Accel::freq = 1000;
float Settings::Accel::range = 4.0;
int16_t Settings::Accel::oneGAsInt = 8192;
int16_t Settings::Accel::xOffset = 0;
int16_t Settings::Accel::yOffset = 0;

bool Settings::RX::stopOnFail = false;

int Settings::PID::freq = 1000;
float Settings::PID::dt = 0.001;

float Settings::Math::constPI = 3.14159265358979323846;

float Settings::IMU::gyroStr = 0.996;
float Settings::IMU::accelStr = 1.0 - Settings::IMU::gyroStr;


#endif