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
        static float cutOff;
        static float sensitivity;
    };
    class Accel
    {
    public:
        static int freq;
        static float cutOff;
        static float range;
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
    };
};

float Settings::Gyro::cutOff = 80.0;
int Settings::Gyro::freq = 8000;
float Settings::Gyro::sensitivity = 125.0;
float Settings::Accel::cutOff = 4.0;
int Settings::Accel::freq = 1000;
float Settings::Accel::range = 4.0;
bool Settings::RX::stopOnFail = false;
int Settings::PID::freq = 1000;

#endif