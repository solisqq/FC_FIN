Output::Output(){}
String Output::coma = ", ";
String Output::newLine = "\n";
String Output::bracketEnd = ")";
String Output::bracketBegin = "(";
void Output::print(const AllowPrint &printable){
    Serial.print(printable.toString());
}
void Output::printLine(const AllowPrint &printable){
    Output::print(printable);
    Serial.print(Output::newLine);
}