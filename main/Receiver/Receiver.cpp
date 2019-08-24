void Receiver::initialize(int RTX_PIN, int medianStr, float irStr)
{
    pinMode(21, INPUT);
    attachInterrupt(digitalPinToInterrupt(21), CPPM_ISR, RISING);
    delay(20);

    Channels = new Axis *[8];
    Channels[0] = &Throttle;
    Channels[1] = &Roll;
    Channels[2] = &Pitch;
    Channels[3] = &Yaw;


    for (int i = 4, j = 0; i < 8; i++, j++)
    {
        Channels[j]->addFilter(new ClosesTo<float>(medianStr, 3000.0));
        Channels[j]->addFilter(new SimpleIR<float>(irStr));
        Channels[i] = &Switch[j];
        Switch[j].setAsSwitch(3);
        Switch[j].addFilter(new ClosesTo<float>(3, 3000.0));
        Channels[i]->addFilter(new Mapper<float>(2000.0, 1000.0, 0.01, 2.0));
        Channels[j]->addFilter(new ExpHighPass<float>(0.3, 10.0));
    }
    Channels[1]->addFilter(new Exponential<float>(2000.0, 1000.0, -25.0, 25.0, 1.4));
    Channels[2]->addFilter(new Exponential<float>(2000.0, 1000.0, -25.0, 25.0, 1.4));
    Channels[3]->addFilter(new Exponential<float>(2000.0, 1000.0, -25.0, 25.0, 1.1));
    Channels[0]->addFilter(new Mapper<float>(2000.0, 1000.0, Settings::Engines::start+80, Settings::Engines::maximum-80));
    Switch[1].setAsSwitch(2);
}

void Receiver::update()
{
    if (!isRadioOn())
    {
        errorNoRadio();
    }
    for (int i = 0; i < 8; i++)
        Channels[i]->update(channel_length[i]);
    
    if(Yaw.get() < -Settings::RX::threshold) 
        staticYaw+=(Yaw.get()+Settings::RX::threshold)/Settings::RX::yawDivider;
    else if(Yaw.get()> Settings::RX::threshold) 
        staticYaw+=(Yaw.get()-Settings::RX::threshold)/Settings::RX::yawDivider;

    inactive = true;
}

bool Receiver::isActive()
{
    if (inactive && errorsCount > 2)
        return false;
    if (channel_length[0]<500)
        return false;
        
    return true;
}

bool Receiver::isRadioOn()
{
    if (inactive)
        return false;
    errorsCount = 0;
    return true;
}

void Receiver::errorNoRadio()
{
    if (errorsCount < 1000)
        errorsCount++;
    channel_length[0] = 1000;
    for (int i = 1; i < 4; i++)
        channel_length[i] = 1500;

    for (int i = 4; i < 8; i++)
        channel_length[i] = 1000;
}

String Receiver::getClassName(){return "Receiver";}
String Receiver::getDebugMsg(bool raw){return toString();}
String Receiver::toString()
{
    String msg = "RX: ";
    for (int i = 0; i < 8; i++)
        msg += Channels[i]->toString() + Output::coma;
    msg+=staticYaw;

    return msg;
}
void Receiver::initCheckRadio() {
    delay(300);
    if(!isActive() && Settings::RX::stopOnFail) {
		Exception rxFail = Exception(Exception::Type::Error, "RX", "No signal");
		Output::throwExc(rxFail);
		EXCEPTION_HOLD(isActive(),rxFail);
	}
    if(isSafetySwitchOn() && Settings::RX::stopOnSwitchHighOnInit) {
        Exception rxFail = Exception(Exception::Type::Error, "RX", "Arm switch is in high state.");
		Output::throwExc(rxFail);
		EXCEPTION_HOLD(!isSafetySwitchOn(),rxFail);
    }
	if(isThrottleHigh() && Settings::RX::stopOnThrottleHigh) {
		Exception rxFail = Exception(Exception::Type::Error, "RX", "Throttle high.");
		Output::throwExc(rxFail);
		EXCEPTION_HOLD(!isThrottleHigh(),rxFail);
	}
}
bool Receiver::isThrottleHigh() {
    if(channel_length[Settings::RX::ID::throttle]>Settings::RX::safeThrottle) return true;
    return false;
}
bool Receiver::isSafetySwitchOn() {
    if(channel_length[Settings::RX::ID::arm]>Settings::RX::safeThrottle) return true;
    return false;
}
Point3D<float> Receiver::getPoint3D() {
    Point3D<float> toRet;
    toRet.updateAll(getForPid(Roll.get()), getForPid(Pitch.get()), staticYaw);
    return toRet;
}
float Receiver::getForPid(float value) {
    if(value < -Settings::RX::threshold || value > Settings::RX::threshold) 
        return value;
    else return 0;
}