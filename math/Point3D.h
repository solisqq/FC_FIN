#pragma once
#ifndef POINT3D_H
#define POINT3D_H

#include "../infac/FilterableValue.h"

template<class Type>
class Point3D {
public:
	enum Var {X=0,Y=1,Z=2};
	//FilterableValue<Type> x,y,z;
	Type x,y,z;
	Point3D() {}
	Point3D(Type X, Type Y, Type Z):x(X),y(Y),z(Z) {}
	void Set(Var var, Type val) {
		if(var==Var::X) x = val;
		else if(var==Var::Y) y = val;
		else z = val;
	}
};
#endif