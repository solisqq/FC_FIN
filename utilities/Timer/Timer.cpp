Timer::Timer(bool precision) {}
void Timer::Init()
{
    toWait = micros();
}
void Timer::Init(long long int time, bool precision)
{
    if (!precision)
        millis_time = millis();
    else
        micros_time = micros();
    toWait = time;
}
bool Timer::IsReady()
{
    if (micros_time == 0)
    {
        if (millis() >= millis_time + toWait)
        {
            millis_time = millis();
            return true;
        }
        else
            return false;
    }
    else
    {
        if (micros() >= micros_time + toWait - 10)
        {
            micros_time = micros();
            return true;
        }
        else
            return false;
    }
}
void Timer::CalculateDifference(long long int *millis_time2)
{
    *millis_time2 = millis() - millis_time;
    millis_time = millis();
}
void Timer::CalculateDifference(unsigned long *micros_time2)
{
    *micros_time2 = micros() - micros_time;
    micros_time = micros();
}
void Timer::CalculateDifference(volatile unsigned long *micros_time2)
{
    *micros_time2 = micros() - micros_time;
    micros_time = micros();
}