#pragma once
#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#define ABSOLUTE_DIFFERENCE(A,B) ((A-B)<0 ? (-(A-B)): (A-B))
#include "../structures/List.h"

template <class Type>
class Algorithms {
public:
    static void quickSort(Type *tab, int left, int right) {
        if(right<=left) return;
        int i = left-1;
        int j = right+1;

        int middle = tab[(left+right)/2];
        while(true) {
            while(middle>tab[++i]);
            while(middle<tab[--j]);
            if(i<=j) {
                Type backup = tab[i];
                tab[i] = tab[j];
                tab[j] = backup;
            }
        }
        if(j>left) 
            quickSort(tab,left,j);

        if(i<right)
            quickSort(tab,i,right);
    }
};
#endif