#pragma once
#ifndef SIMPLEIR_H
#define SIMPLEIR_H

#include "../infac/Filter.h"

template<class Type>
class SimpleIR : public Filter<Type> {
    float = 
    
    SimpleIR(Type *value, int st) {
        val = value;
    }
    virtual void Update() {
        *val = *val * filterStrength; 
    }
};

#endif