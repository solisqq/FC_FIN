#pragma once
#ifndef UTIL_H
#define UTIL_H

#include "../structures/List.h"
#include <string>

class Utilities
{
public:
    static List<String> explode(const String &source, const char delimiter) {
        List<String> toRet;
        String word="";
        int length = source.length();
        for(int i=0; i<length; i++) {
            if(source[i] == delimiter) {
                toRet.pushBack(word);
                word="";
            }
            else word+=source[i];
        }
        if(word.length()>0) toRet.pushBack(word);
        return toRet;
    }
};

#endif