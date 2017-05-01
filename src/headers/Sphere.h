#ifndef SPHERE_H
#define SPHERE_H
#include "Vector3.h"
#include "Ray.h"
#include "Geometry.h"
class Sphere:public Geometry{
	public:
	double radius;
	Sphere(double radius=1)noexcept:radius(radius){}
	IntersectInfo testIntersect(Ray r)const noexcept override;
};
#endif //SPHERE_H