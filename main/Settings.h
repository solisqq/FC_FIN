#pragma once
#ifndef SETTINGS_FC_H
#define SETTINGS_FC_H

#include "../math/Point3D/Vector.h"
#include "../structures/List.h"
#include "../utilities/utilities.h"
#include <string.h>

class Settings
{
private:
public:
    class PID
    {
    public:
        static int freq;
        static float dt;
        static Vector<float> P;
        static Vector<float> I;
        static Vector<float> D;
        static float DFilter;
        static String toString();
    };
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
        static float xOffset;
        static float yOffset;
    };
    class RX
    {
    public:
        static bool stopOnFail;
        static float threshold;
        static float yawDivider;
        static bool stopOnThrottleHigh;
        static bool stopOnSwitchHighOnInit;
        static int safeThrottle;
        static float IRStr;
        static float Expo;
        class ID {
        public:
            static int throttle;
            static int arm;
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
        static int calibTime;
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
        static int pwmFreq;
        static float multiplier;
    };
    class SD {
    public:
        static int CSPin;
    };
    static void readFromFile(String settings);
    static String getSettingsFileString();
};

float Settings::Gyro::cutOff = 70.0;
int Settings::Gyro::freq = 8000;
int Settings::Gyro::calibThreshold = 80;//100
float Settings::Gyro::sensitivity = 120.0;

float Settings::Accel::cutOff = 4.0;
int Settings::Accel::freq = 1000;
float Settings::Accel::range = 4.0;
int16_t Settings::Accel::oneGAsInt = 8192;
float Settings::Accel::xOffset = -1.0;
float Settings::Accel::yOffset = -5.0;

bool Settings::RX::stopOnFail = true;
bool Settings::RX::stopOnThrottleHigh = true;
bool Settings::RX::stopOnSwitchHighOnInit = true;
float Settings::RX::threshold = 0.4;
float Settings::RX::yawDivider = 4;
int Settings::RX::safeThrottle = 1320;
int Settings::RX::ID::throttle = 0;
int Settings::RX::ID::arm = 5;
float Settings::RX::IRStr = 0.91;
float Settings::RX::Expo = 1.1;

int Settings::PID::freq = 1000;
float Settings::PID::dt = 1.0/Settings::PID::freq;
//----------------------------------------------R----P-----Y----
//Vector<float> Settings::PID::P = Vector<float>(2.5, 2.5, 1.5);
Vector<float> Settings::PID::P = Vector<float>(0.0, 0.0, 0.0);
Vector<float> Settings::PID::I = Vector<float>(0.0, 0.0, 0.0);
Vector<float> Settings::PID::D = Vector<float>(1.0, 1.0, 1.0);
float Settings::PID::DFilter = 140;

float Settings::Math::constPI = 3.14159265358979323846;

float Settings::IMU::gyroStr = 0.9996;
int Settings::IMU::calibTime = 150;//150

int Settings::Engines::minimum = 1148;
int Settings::Engines::maximum = 1832;
int Settings::Engines::start = 1148;
int Settings::Engines::fl = 26; //27
int Settings::Engines::fr = 27; //14
int Settings::Engines::bl = 14; //26
int Settings::Engines::br = 25; //25
int Settings::Engines::pwmFreq = 12000;
float Settings::Engines::multiplier = 1.0;

int Settings::SD::CSPin = 17;

void Settings::readFromFile(String settings) {
    List<String> data = Utilities::explode(settings, '\n');
    if(data.Count<8) return;
    Output::printLine(data.toString());
    PID::P = Vector<float>(data.getAndPopFront().toFloat(), data.getAndPopFront().toFloat(), data.getAndPopFront().toFloat());
    PID::I = Vector<float>(data.getAndPopFront().toFloat(), data.getAndPopFront().toFloat(), data.getAndPopFront().toFloat());
    PID::D = Vector<float>(data.getAndPopFront().toFloat(), data.getAndPopFront().toFloat(), data.getAndPopFront().toFloat());
    Settings::Accel::xOffset = data.getAndPopFront().toFloat();
    Settings::Accel::yOffset = data.getAndPopFront().toFloat();

    Settings::PID::DFilter = data.getAndPopFront().toFloat();
    Settings::RX::Expo = data.getAndPopFront().toFloat();
    Settings::RX::IRStr = data.getAndPopFront().toFloat();
    Settings::Accel::cutOff = data.getAndPopFront().toFloat();
    Settings::Gyro::cutOff = data.getAndPopFront().toFloat();
    Settings::IMU::gyroStr = data.getAndPopFront().toFloat();
}

String Settings::PID::toString() {
    return Settings::PID::P.toString() + ", " + Settings::PID::I.toString() + ", " + Settings::PID::D.toString();
}
String Settings::getSettingsFileString() {
    String toRet = "";
    toRet+=(String)PID::P.x+'\n';
    toRet+=(String)PID::P.y+'\n';
    toRet+=(String)PID::P.z+'\n';
    toRet+=(String)PID::I.x+'\n';
    toRet+=(String)PID::I.y+'\n';
    toRet+=(String)PID::I.z+'\n';
    toRet+=(String)PID::D.x+'\n';
    toRet+=(String)PID::D.y+'\n';
    toRet+=(String)PID::D.z+'\n';
    toRet+=(String)Settings::Accel::xOffset+'\n';
    toRet+=(String)Settings::Accel::yOffset+'\n';
    toRet+=(String)Settings::PID::DFilter+'\n';
    toRet+=(String)Settings::RX::Expo+'\n';
    toRet+=(String)Settings::RX::IRStr+'\n';
    toRet+=(String)Settings::Accel::cutOff+'\n';
    toRet+=(String)Settings::Gyro::cutOff+'\n';
    toRet+=(String)Settings::IMU::gyroStr+'\n';
    return toRet;
}
#endif