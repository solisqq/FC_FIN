#include "Filter.h"
#include "../structures/List.h"
#include "../infac/AllowPrint.h"

template <class Type>
class FilterableValue: public AllowPrint {
public:
	Type value;
	FilterableValue(){value=0;}
	List<Filter<Type>*> filters;
	void update(Type val) {
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