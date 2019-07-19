#pragma once
#ifndef PAIRR_H
#define PAIRR_H

template <class T1, class T2>
class Pair {
public:
    T1 first;
    T2 second;
	Pair(T1 _val1, T2 _val2): first(_val1), second(_val2) {}
};


#endif