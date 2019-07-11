CommandSystem::CommandSystem() {}
void CommandSystem::setDebugOnCMD(Debug &_debugger, DebugItem &_item, const String &cmd) {
    commands.Insert(cmd, new DebugAddAction(_debugger, _item));
}
bool CommandSystem::doActionOnCMD(const String &cmd) {
    Action *act = commands.Find("cmd");
    if(act!=nullptr) {
        act->execute(nullptr);
        return true;
    }
    return false;
}