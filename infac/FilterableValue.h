#include "Filter.h"
#include "../structures/List.h"

template <class Type>
class FilterableValue {
public:
	Type value;
	FilterableValue(){value=0;}
	List<Filter<Type>> filters;
	void addFilter(Filter<Type>& filter) {
		filters.pushBack(filter);
	}
};