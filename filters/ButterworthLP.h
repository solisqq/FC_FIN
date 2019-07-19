#pragma once
#ifndef BUTTERWORTH_LP_H
#define BUTTERWORTH_LP_H
#define Butterworth_ORDER 4

#include "stock/Iir.h"
#include "../infac/Filter.h"
#include "../main/Settings.h"

template<class Type>
class ButterworthLP: public Filter<Type> {
	Iir::Butterworth::LowPass<Butterworth_ORDER> bworth;
public:
	ButterworthLP(float freq, float cutoff) {
		bworth.setup(Butterworth_ORDER, freq, cutoff);
    }

    virtual void update(Type newVal) {
        Filter<Type>::filtered = bworth.filter(static_cast<double>(newVal));
    }
};

#endif