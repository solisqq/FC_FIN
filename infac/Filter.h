#pragma once
#ifndef FILTER_H
#define FILTER_H

template <class Type>
class Filter {
public:
	Type *filtered;
	void setVal(Type *_val) {filtered = _val;}
	virtual void update(Type newVal) = 0;
};

#endif