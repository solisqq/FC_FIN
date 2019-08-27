#define isValid(x) x!=nullptr ? true : false
#define WAIT_SHORT delay(10)
#define WAIT_LONG delay(50)
#include "../utilities/Debug/Debug.h"
Debug debugger;

#include "Settings.h"
#include "../structures/List.h"
#include "../utilities/Output/Output.h"
#include "../filters/SimpleIR.h"
#include "../math/Point3D/Point3D.h"
#include "../utilities/Timer/Timer.h"
#include "../utilities/CommandSystem/CommandSystem.h"
#include "Receiver/Receiver.h"
#include "../utilities/Exceptions/Exception.h"
#include "../sensors/IMU.h"
#include "../utilities/SDCard/SDCard.h"
#include "Steering.h"
#include "PID.h"

CommandSystem cmd;
List<Exception> exceptions;
PID pid;

Timer debugTimer;
Timer rxTimer;
Timer inputTimer;
String command;

IMU imu;
Receiver rx;
Steering copter;

SDCard mem;

TaskHandle_t TaskIMU;

void IMUCalculate(void * parameter) {
    for(;;) {
        imu.update();
    }
}
