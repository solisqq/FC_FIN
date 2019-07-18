#pragma once
#ifndef EXCEPTION_H
#define EXCEPTION_H
#define EXCEPTION_HOLD(x,expc) while(!x) {} Output::succExc(expc);

#include "../Output/Output.h"

class Exception {
public:
    enum Type {
        Warning = 0,
        Error = 1,
        Critical = 2
    };

    Type type;
    String source;
    String text;

    Exception(Type _type, const String _src, const String _text):
        type(_type), source(_src), text(_text) {}
};

#endif