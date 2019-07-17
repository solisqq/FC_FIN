#pragma once
#ifndef ABSOLUTEHIGHPASS_H
#define ABSOLUTEHIGHPASS_H

#include "../infac/Filter.h"
#include "../algorithms/algorithms.h"

template<class Type>
class AbsoluteHighPass : public Filter<Type> {
private:
    float low=0.0;
    float high=0.0;
    bool initialized=false;
    Type passDifference = 0;
public:
    AbsoluteHighPass(Type _passDifference): passDifference(_passDifference) {}
    virtual void update(Type newVal) {
        if(!initialized) {
            Filter<Type>::filtered = newVal;
            initialized = true;
            return;
        }
        if( ABSOLUTE_DIFFERENCE(Filter<Type>::filtered, newVal) < passDifference)
            return;
        Filter<Type>::filtered = newVal; 
    }
};

#endif