#pragma once
#include "startup.h"

void mainLoop()
{
    if (timer.IsReady())
    {
        randNumberX = random(300);
        randNumberY = random(300);
        randNumberZ = random(300);
        somePoint.updateAll(
            static_cast<int>(randNumberX),
            static_cast<int>(randNumberY),
            static_cast<int>(randNumberZ)
        );
        Output::printLine(somePoint);
    }
}