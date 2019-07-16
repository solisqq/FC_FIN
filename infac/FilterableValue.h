#pragma once
#ifndef FILTERABLEVALUE_H
#define FILTERABLEVALUE_H

#include "Filter.h"
#include "../structures/List.h"
#include "../infac/AllowPrint.h"

template <class Type>
class FilterableValue: public AllowPrint {
public:
	volatile Type value;
	FilterableValue(){value=0;}
	List<Filter<Type>*> filters;
	void update(Type val) {
		if(filters.Count==0) {
			value = val;
			return;
		}
		typename List<Filter<Type>*>::Node *current = filters.front;
		
		while(current!=nullptr) {
			current->val->update(val);
			current = current->next;
		}
	}
	void addFilter(Filter<Type>* filter) {
		filter->filtered = &value;
		filters.pushBack(filter);
	}
	virtual String toString() {return static_cast<String>(value);}
};

#endif