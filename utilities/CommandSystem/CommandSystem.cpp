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