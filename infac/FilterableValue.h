#include <list>
#include "Filter.h"

template <class Type>
class FilterableValue {
	Type value;
	std::list<Filter<Type>> filters;
};