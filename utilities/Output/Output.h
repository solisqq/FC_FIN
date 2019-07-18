#pragma once
#ifndef OUTPUT_H
#define OUTPUT_H

#include "../../infac/AllowPrint.h"
#include "../Exceptions/Exception.h"

class Output {
public:
    static String coma;
    static String newLine;
    static String bracketEnd;
    static String bracketBegin;
    static long baudRate;
    static void initialize();
    static void print(AllowPrint &printable);
    static void throwExc(List<Exception> &exceptions, const Exception exc);
    static void throwExc(const Exception exc);
    static void succExc(const Exception exc);
    static void succExc(List<Exception> &exceptions);
    static void printLine(AllowPrint &printable);
    static void printLine(const String &text);
    static void printLine(char ch);
    static void printLine(int toPrint, int prec=3);
    static void printLine(float toPrint, int prec=3);
    static void printLine(double toPrint, int prec=3);
    static void Append(int toPrint, String valueName = "");
    static void Append(float toPrint, String valueName = "", int prec=3);
    static void Append(double toPrint, String valueName = "",int prec=3);
    static void info(const String text);
    static void Show();

private:
    Output();
};

#include "Output.cpp"

#endif