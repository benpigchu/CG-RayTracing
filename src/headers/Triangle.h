#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Geometry.h"
#include "Vector3.h"
#include "Ray.h"

// this triangle is only used for mesh components
struct Triangle{
	Vector3 nm;
	Vector3 point[3];
	IntersectInfo testIntersect(Ray r)const noexcept;
};

#endif //TRIANGLE_H