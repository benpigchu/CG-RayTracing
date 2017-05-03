#ifndef SQUARE_H
#define SQUARE_H
#include "Vector3.h"
#include "Ray.h"
#include "Geometry.h"

// square on xy plane facing z+
class Square:public Geometry{
	public:
	double side;
	Square(double side)noexcept:side(side){}
	IntersectInfo testIntersect(Ray r)const noexcept override;
};

#endif //SQUARE_H