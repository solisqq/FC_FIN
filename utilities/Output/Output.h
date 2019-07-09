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
    static void print(const AllowPrint &printable);
    static void printLine(const AllowPrint &printable);
private:
    Output();
};

#include "Output.cpp"

#endif