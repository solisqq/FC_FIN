#pragma once
#include "globalObjects.h"
#include "../filters/SimpleIR.h"
#include "../math/Point3D/Point3D.h"

void initialize(){
	Point3D<float> somePoint;
	somePoint.x.addFilter(SimpleIR());
}
