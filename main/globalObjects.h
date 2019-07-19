#define isValid(x) x!=nullptr ? true : false
#define WAIT_SHORT delay(10)
#define WAIT_LONG delay(50)
#include "Settings.h"
#include "../structures/List.h"
#include "../utilities/Output/Output.h"
#include "../utilities/Debug/Debug.h"
#include "../filters/SimpleIR.h"
#include "../math/Point3D/Point3D.h"
#include "../utilities/Timer/Timer.h"
#include "../utilities/CommandSystem/CommandSystem.h"
#include "Receiver/Receiver.h"
#include "../utilities/Exceptions/Exception.h"
#include "../sensors/IMU.h"


Debug debugger;
CommandSystem cmd;
List<Exception> exceptions;

Timer debugTimer;
Timer rxTimer;

IMU imu;
Receiver rx;
