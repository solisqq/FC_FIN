Debug::Debug() {prevTime=micros();}
void Debug::Show()
{
    typename List<DebugItem *>::Node *current = items.front;
    while (current != nullptr)
    {
        Output::printLine(current->val->getDebugMsg());
        current = current->next;
    }
}
void Debug::CalculateFreq()
{
    counter++;
    if (prevTime + 1000000 <= micros())
    {
        prevTime = micros();
        Serial.print("Freq: ");
        Serial.print((int)counter);
        Serial.println("");
        counter = 0;
    }
}