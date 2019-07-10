Debug::Debug() {}
void Debug::Show()
{
    typename List<DebugItem *>::Node *current = items.front;
    while (current != nullptr)
    {
        Output::printLine(current->val->getDebugMsg());
        current = current->next;
    }
}