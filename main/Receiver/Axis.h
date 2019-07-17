#pragma once
#ifndef AXIS_H
#define AXIS_H

#include "../../infac/FilterableValue.h"
#include "../../infac/AllowPrint.h"

class Axis {
private:
    FilterableValue<float> filtered;
    int isSwitch = 0;
public:
    float get() {
        if(isSwitch<1) return filtered.value;
        if(filtered.value < 0.5) return 0;
        else if (filtered.value > 1.5) return 2;
        else return 1;
    }
    void addFilter(Filter<float> *filter) {
        filtered.addFilter(filter);
    }
    void update(int toUpd) {
        filtered.update(static_cast<float>(toUpd));
    }
    virtual String toString() {
        return static_cast<String>(get());
    }
    void setAsSwitch(int states){
        isSwitch = states;
    }
};

#endif