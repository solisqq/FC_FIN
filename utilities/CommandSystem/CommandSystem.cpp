CommandSystem::CommandSystem() {}
void CommandSystem::setDebugOnCMD(Debug &_debugger, DebugItem &_item, const String &cmd) {
    commands.Insert(cmd, new DebugAddAction(_debugger, _item));
}
void CommandSystem::setDebugClearOnCMD(Debug &_debugger, const String &cmd) {
    commands.Insert(cmd, new DebugClear(_debugger));
}
void CommandSystem::setShow(const String &cmd) {
    commands.Insert(cmd, new CMDShow());
}

bool CommandSystem::doActionOnCMD(const String &cmd) {
    List<String> splited = Utilities::explode(cmd,' ');
    Action *act = commands.Find(splited.front->val);
    splited.popFront();
    if(isValid(act)) {
        act->execute(splited);
        return true;
    }
    return false;
}

void CommandSystem::setSet(SDCard *_memory, SPIClass *_cSPI, const String &cmd, float *val) {commands.Insert(cmd, new CMDSet(_memory, _cSPI, val));}
void CommandSystem::setSet(SDCard *_memory, SPIClass *_cSPI, const String &cmd, double *val) {commands.Insert(cmd, new CMDSet(_memory, _cSPI, val));}
void CommandSystem::setSet(SDCard *_memory, SPIClass *_cSPI, const String &cmd, Vector<float> *val) {commands.Insert(cmd, new CMDSet(_memory, _cSPI, val));}
void CommandSystem::setSet(SDCard *_memory, SPIClass *_cSPI, const String &cmd, int *val) {commands.Insert(cmd, new CMDSet(_memory, _cSPI, val));}
void CommandSystem::setSet(SDCard *_memory, SPIClass *_cSPI, const String &cmd, String *val) {commands.Insert(cmd, new CMDSet(_memory, _cSPI, val));}
