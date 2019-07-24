CommandSystem::CommandSystem() {}
void CommandSystem::setDebugOnCMD(Debug &_debugger, DebugItem &_item, const String &cmd) {
    commands.Insert(cmd, new DebugAddAction(_debugger, _item));
}
void CommandSystem::setDebugClearOnCMD(Debug &_debugger, const String &cmd) {
    commands.Insert(cmd, new DebugClear(_debugger));
}
bool CommandSystem::doActionOnCMD(const String &cmd) {
    Action *act = commands.Find(cmd);
    if(isValid(act)) {
        act->execute(nullptr);
        return true;
    }
    return false;
}