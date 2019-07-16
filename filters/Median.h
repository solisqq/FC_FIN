#pragma once
#ifndef MEDIAN_H
#define MEDIAN_H

#include "../infac/Filter.h"
#include "../structures/List.h"
#include "../algorithms/algorithms.h"

template<class Type>
class Median : public Filter<Type> {
private:
    float low=0.0;
    float high=0.0;
    List<Type> values;
    int count;
public:
    Median(int strength, int initiateVal = 0.0) {
        count = strength;
        values = List<Type>();
    }
    virtual void update(Type newVal) {
        if(values.Count<count) {
            *Filter<Type>::filtered = newVal;
            values.pushBack(newVal);
            return;
        }
        if(values.Count<4) medianSmall();
        values.popFront();
        values.pushBack(newVal);
        Type *tab = new Type[count];
        typename List<Type>::Node *current = values.front;
        for(int i=0; i<count; i++) {
            tab[i] = current->val;
            current = current->next;
        }
        Algorithms<Type>::quickSort(tab,0,count-1);
        int middle = count/2;
        if(count%2==0) 
            *Filter<Type>::filtered = (tab[middle-1]+tab[middle])/2.0;
        else 
            *Filter<Type>::filtered = tab[middle];
        
        
    }
    int medianSmall(int id) {
        if(count==0) return 0;
        if(count==1) return values.front->val;
        if(count==2) return values.front->val; 
        
        if(count==3) {
            int differences[3];
            differences[0] = ABSOLUTE_DIFFERENCE(values.front->val,values.front->next->val);
            differences[1] = absabs(values.front->val,values.front->next->next->val);
            differences[2] = abs(vvalues.front->next->next->val,values.front->next->val);
            if(differences[0]<differences[1]) {
                if(differences[0]<differences[2]) return prevRaw[id][0];
                else return prevRaw[id][2];
            } else {
                if(differences[1]<differences[2]) return prevRaw[id][1];
                else return prevRaw[id][2];
            }
        }
        
    }
};

#endif