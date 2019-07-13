String textToPrintOutput = "";

Output::Output(){}
String Output::coma = ", ";
String Output::newLine = "\n";
String Output::bracketEnd = ")";
String Output::bracketBegin = "(";

long Output::baudRate = 115200;

void Output::initialize() {
    Serial.begin(baudRate);
    delay(10);    
}
void Output::print(AllowPrint &printable){
    Serial.print(printable.toString());
}
void Output::printLine(AllowPrint &printable){
    Output::print(printable);
    Serial.print(Output::newLine);
}
void Output::printLine(const String &text){Serial.println(text);}
void Output::printLine(char ch) {Serial.println(ch);}
void Output::printLine(int toPrint, int prec){Serial.println(toPrint);}
void Output::printLine(float toPrint, int prec){
    Serial.print(toPrint, prec);
    Serial.println("");
}
void Output::printLine(double toPrint, int prec){
    Serial.print(toPrint, prec);
    Serial.println("");
}

void Output::Append(int toPrint, String valueName){
    if(valueName=="") 
        textToPrintOutput += static_cast<String>(toPrint)+Output::coma;
    else 
        textToPrintOutput += valueName+ ": "+static_cast<String>(toPrint)+Output::coma;
}
void Output::Append(float toPrint, String valueName, int prec){
    String converted = static_cast<String>(toPrint);
    int index = converted.indexOf(".");
    converted = converted.substring(0,index+prec);
    if(valueName=="") 
        textToPrintOutput += converted+Output::coma;
    else 
        textToPrintOutput += valueName+ ": "+converted+Output::coma;
}
void Output::Append(double toPrint, String valueName,int prec){
    String converted = static_cast<String>(toPrint);
    int index = converted.indexOf(".");
    converted = converted.substring(0,index+prec);
    if(valueName=="") 
        textToPrintOutput += converted+Output::coma;
    else 
        textToPrintOutput += valueName+ ": "+converted+Output::coma;
}
void Output::Show() {
    if(textToPrintOutput!="")
        Serial.println(textToPrintOutput.substring(0,textToPrintOutput.length()-2));
}

