#pragma once
#ifndef AXIS_H
#define AXIS_H

#include "../../infac/FilterableValue.h"
#include "../../infac/AllowPrint.h"

class Axis {
private:
    FilterableValue<float> filtered;
public:
    float get() {
        return filtered.value;
    }
    void addFilter(Filter<float> *filter) {
        filtered.addFilter(filter);
    }
    void update(int toUpd) {
        filtered.update(static_cast<float>(toUpd));
    }
    virtual String toString() {
        return filtered.toString();
    }
};

#endif