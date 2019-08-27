#pragma once
#ifndef FILTERABLEVALUE_H
#define FILTERABLEVALUE_H

#include "Filter.h"
#include "../structures/List.h"
#include "../infac/AllowPrint.h"

template <class Type>
class FilterableValue: public AllowPrint {
public:
	Type value;
	FilterableValue(){}
	List<Filter<Type>*> filters;
	void update(Type val) {
		if(filters.Count==0) {
			value = val;
			return;
		}
		typename List<Filter<Type>*>::Node *current = filters.front;
		if(current!=nullptr) {
			filters.front->val->update(val);
			current = current->next;

			while(current!=nullptr) {
				current->val->update(current->prev->val->filtered);
				current = current->next;
			}
			value = filters.back->val->filtered;
		}
	}
	void reset() {
		typename List<Filter<Type>*>::Node *current = filters.front;
		if(current!=nullptr) {
			filters.front->val->reset();
			current = current->next;
		}
	}
	void addFilter(Filter<Type>* filter) {
		filters.pushBack(filter);
	}
	void addFilter(List<Filter<Type>*> filter) {
		filters.Union(filter);
	}
	virtual String toString() {return static_cast<String>(value);}
};

#endif