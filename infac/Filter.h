#pragma once
#ifndef FILTER_H
#define FILTER_H

template <class Type>
class Filter {
public:
	Type *val;
	void SetVal(Type *_val) {val = _val;}
	virtual void Update() = 0;
};

#endif