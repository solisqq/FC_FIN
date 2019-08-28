#pragma once
#ifndef COMMANDSYSTEM_H
#define COMMANDSYSTEM_H

#include "../../structures/Trie.h"
#include "../Debug/Debug.h"
#include "../../infac/Action.h"
#include "Commands.h"

class CommandSystem
{
public:
    Trie<Action *> commands;
    CommandSystem();
    void setDebugOnCMD(Debug &debugger, DebugItem &_item, const String &cmd);
    void setDebugClearOnCMD(Debug &_debugger, const String &cmd);
    bool doActionOnCMD(const String &cmd);
    void setShow(const String &cmd);
    void setSet(SDCard *_memory, SPIClass *_cSPI, const String &cmd, float *val);
    void setSet(SDCard *_memory, SPIClass *_cSPI, const String &cmd, double *val);
    void setSet(SDCard *_memory, SPIClass *_cSPI, const String &cmd, Vector<float> *val);
    void setSet(SDCard *_memory, SPIClass *_cSPI, const String &cmd, int *val);
    void setSet(SDCard *_memory, SPIClass *_cSPI, const String &cmd, String *val);
};

#include "CommandSystem.cpp"
#endif