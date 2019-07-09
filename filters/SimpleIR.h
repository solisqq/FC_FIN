#pragma once
#ifndef SIMPLEIR_H
#define SIMPLEIR_H

#include "../infac/Filter.h"

template<class Type>
class SimpleIR : public Filter<Type> {
private:
    float low=0.0;
    float high=0.0;
public:
    SimpleIR(float strength) {CalcStr(strength);}
    SimpleIR(Type *value, float strength) {
        Filter<Type>::filtered = value;
        CalcStr(strength);
    }
    virtual void update(Type newVal) {
        *Filter<Type>::filtered = (newVal * low) + (*Filter<Type>::filtered * high); 
    }
    void CalcStr(float strength) {
        low = 1.0 - strength;
        high = strength;
    }
};

#endif