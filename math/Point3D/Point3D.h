#pragma once
#ifndef POINT3D_H
#define POINT3D_H

#include "../../infac/FilterableValue.h"
#include "../../infac/AllowPrint.h"
#include "Vector.h"
#include "../../infac/DebugItem.h"

#define FOR_EACH_NOBR for(int i=0;i<3;i++)
#define FOR_EACH_BR for(int i=0;i<3;i++) {

template<class Type>
class Point3D : public AllowPrint, public DebugItem {
public:
	enum Var {X=0,Y=1,Z=2};
	FilterableValue<Type> x,y,z;
	Point3D() {x.value=0; y.value=0; z.value=0;}
	Point3D(Type X, Type Y, Type Z):x(X),y(Y),z(Z) {}
	void update(Var var, Type val) {
		if(var==Var::X) x.update(val);
		else if(var==Var::Y) y.update(val);
		else z.update(val);
	}
	void updateAll(Type _x, Type _y, Type _z) {
		x.update(_x);
		y.update(_y);
		z.update(_z);
	}
	void updateAll(Vector<Type> vect) {
		x.update(vect.x);
		y.update(vect.y);
		z.update(vect.z);
	}
	void resetVals() {
		x.reset();
		y.reset();
		z.reset();
		x.value = 0;
		y.value = 0;
		z.value = 0;
	} 
	static Point3D<Type> toPoint3D(Vector<Type> vect) {
		Point3D<Type> toRet;
		toRet.x.value = vect.x;
		toRet.y.value = vect.y;
		toRet.z.value = vect.z;
		return toRet;
	}
	Vector<Type> getVector() {
		Vector<Type> toRet;
		toRet.x = x.value;
		toRet.y = y.value;
		toRet.z = z.value;
		return toRet;
	}
	Type& operator[] (int i) {
        if(i<1) return this->x;
        if(i>1) return this->z;
        return this->y;
    }
	virtual String toString() {
		return "Point3D("+
			x.toString()+Output::coma+
			y.toString()+Output::coma+
			z.toString()+Output::bracketEnd
		;
	}
	virtual String getDebugMsg(bool raw=false) {
		if(!raw) return toString();
		else return ""+x.toString()+Output::coma+y.toString()+Output::coma+z.toString();
	}
	virtual String getClassName() {return "Point3D";}
};

#endif