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
        Channels[i]->addFilter(new Mapper<float>(2000.0, 1000.0, 0.01, 2.0, false));
        Channels[j]->addFilter(new Mapper<float>(2000.0, 1000.0, -100.0, 100.0));
    }
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
    inactive = true;
}

bool Receiver::isActive()
{
    if (inactive && errorsCount > 2)
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

    return msg;
}