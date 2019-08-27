CommandSystem::CommandSystem() {}
void CommandSystem::setDebugOnCMD(Debug &_debugger, DebugItem &_item, const String &cmd) {
    commands.Insert(cmd, new DebugAddAction(_debugger, _item));
}
void CommandSystem::setDebugClearOnCMD(Debug &_debugger, const String &cmd) {
    commands.Insert(cmd, new DebugClear(_debugger));
}
bool CommandSystem::doActionOnCMD(const String &cmd) {
    List<String> splited;
    String current="";
    for(int i=0; i<cmd.length(); i++) {
        if(cmd[i]!=' ') {
            current+=cmd[i];
        } else {
            splited.pushBack(current);
            current = "";
        }
    }
    Action *act = commands.Find(cmd);
    if(isValid(act)) {
        act->execute(nullptr);
        return true;
    }
    return false;
}