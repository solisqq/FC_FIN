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
    static float calcAvg(Type *tab, int count) {
        Type val = 0;
        for(int i=0; i<count; i++)
            val+=tab[i];
        
        return val/count;
    }
    static double calcAvg(const List<Type> &_list) {
        double val = 0;
        for(typename List<Type>::Node *current = _list.front; current!=nullptr; current = current->next) 
            val+=current->val;
        
        return val/_list.Count;
    }
};
#endif