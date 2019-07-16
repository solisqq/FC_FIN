#pragma once
#ifndef CLOSESTO_H
#define CLOSESTO_H

#include "../infac/Filter.h"
#include "../structures/List.h"
#include "../algorithms/algorithms.h"

template<class Type>
class ClosesTo : public Filter<Type> {
private:
    float low=0.0;
    float high=0.0;
    List<Type> values;
    int count;
    Type maxVal;
public:
    ClosesTo(int strength, Type max) {
        maxVal = max;
        count = strength;
        values = List<Type>();
    }
    virtual void update(Type newVal) {
        if(values.Count<count) {
            Filter<Type>::filtered = newVal;
            values.pushBack(newVal);
            return;
        }
        values.popFront();
        values.pushBack(newVal);

        typename List<Type>::Node *current = values.front;
        typename List<Type>::Node *min = values.front;
        Type currMin = maxVal;
        while(current!=nullptr) {
            Type temporary = ABSOLUTE_DIFFERENCE(current->val, Filter<Type>::filtered);
            if( temporary < currMin) {
                min = current;
                currMin = temporary;
            }
            current = current->next;
        }
        Filter<Type>::filtered = min->val;
    }
};

#endif