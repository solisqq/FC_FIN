#include "Filter.h"
#include "../structures/List.h"

template <class Type>
class FilterableValue {
public:
	Type value;
	FilterableValue(){value=0;}
	List<Filter<Type>> filters;
	void update(Type val) {
		typename List<Filter<Type>>::Node *current = filters.front;
		
		for(int i=0; i<filters.Count; i++) {
			current = current->next;
			current.update();
		}
	}
	void addFilter(Filter<Type>& filter) {
		filter.val = *value;
		filters.pushBack(filter);
	}
};