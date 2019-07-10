#pragma once
#include "startup.h"

void mainLoop()
{
    if(debugTimer.IsReady()) 
        debugger.Show();
    
}