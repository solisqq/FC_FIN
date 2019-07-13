#pragma once
#ifndef OUTPUT_H
#define OUTPUT_H

#include "../../infac/AllowPrint.h"

class Output {
public:
    static String coma;
    static String newLine;
    static String bracketEnd;
    static String bracketBegin;
    static long baudRate;
    static void initialize();
    static void print(AllowPrint &printable);
    static void printLine(AllowPrint &printable);
    static void printLine(const String &text);
    static void printLine(char ch);
    static void printLine(int toPrint, int prec=3);
    static void printLine(float toPrint, int prec=3);
    static void printLine(double toPrint, int prec=3);
    static void Append(int toPrint, String valueName = "");
    static void Append(float toPrint, String valueName = "", int prec=3);
    static void Append(double toPrint, String valueName = "",int prec=3);
    static void Show();

private:
    Output();
};

#include "Output.cpp"

#endif