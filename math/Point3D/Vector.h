#ifndef VECTOR_H
#define VECTOR_H

#include <String.h>
#define RAD_MULTI 0.01745329251
#define FOR_ALL_VECTORS for(int i=0;i<3;i++)

template <class Type> 
class Vector : public AllowPrint
{
public:
   	Type x,y,z;
   	Vector(){x=0;y=0;z=0;}
   	Vector(Type val){x=val;y=val;z=val;}
   	Vector(bool nulify){}
   	Vector(Type x, Type y, Type z): x(x), y(y), z(z){}
   	Vector<Type> InvertXY() {
   		Vector<Type> inverted(this->y*(-1),this->x*(-1),this->z);
   		return inverted;
   	}
   	Vector<Type> toRadians() {return (*this)*RAD_MULTI;}
   	virtual String toString() {
		   return "Vector("+
		   (String)x+Output::coma+
		   (String)y+Output::coma+
		   (String)z+Output::bracketEnd;
	}
   	Type& operator[] (int i) {
        if(i<1) return this->x;
        if(i>1) return this->z;
        return this->y;
    }
    Vector<Type>& operator=(const Vector<Type>& right)
	{
	    this->x = right.x;
	    this->y = right.y;
	    this->z = right.z;
	    return *this;
	}
    Vector<Type>& operator+=(const Vector<Type>& right)
	{
	    this->x += right.x;
	    this->y += right.y;
	    this->z += right.z;
	    return *this;
	}
	Vector<Type>& operator/=(const Vector<Type>& right)
	{
	    this->x /= right.x;
	    this->y /= right.y;
	    this->z /= right.z;
	    return *this;
	}
	Vector<Type>& operator/(const Vector<Type>& right)
	{
		Type toRet;
	    toRet.x = this->x/right.x;
	    toRet.y = this->y/right.y;
	    toRet.z = this->z/right.z;
	    return toRet;
	}
	Vector<Type>& operator*=(const Vector<Type>& right)
	{
	    this->x *= right.x;
	    this->y *= right.y;
	    this->z *= right.z;
	    return *this;
	}
	Vector<Type>& operator*=(double right)
	{
	    this->x *= right;
	    this->y *= right;
	    this->z *= right;
	    return *this;
	}
	Vector<Type>& operator/=(float right)
	{
	    this->x /= right;
	    this->y /= right;
	    this->z /= right;
	    return *this;
	}
	Vector<Type>& operator*(const Vector<Type>& right)
	{
		Type toRet;
	    toRet.x = this->x*right.x;
	    toRet.y = this->y*right.y;
	    toRet.z = this->z*right.z;
	    return toRet;
	}
	Vector<Type>& operator-=(const Vector<Type>& right)
	{
	    this->x -= right.x;
	    this->y -= right.y;
	    this->z += right.z;
	    return -this;
	}
	Vector<Type>& operator+(const Vector<Type>& right)
	{
		Type toRet;
	    toRet.x = this->x + right.x;
	    toRet.y = this->y + right.y;
	    toRet.z = this->z + right.z;
	    return toRet;
	}
	Vector<Type>& operator-(const Vector<Type>& right)
	{
		Type toRet;
	    toRet.x = this->x - right.x;
	    toRet.y = this->y - right.y;
	    toRet.z = this->z - right.z;
	    return toRet;
	}
};

#endif