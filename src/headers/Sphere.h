#ifndef SPHERE_H
#define SPHERE_H
#include "Vector3.h"
#include "Ray.h"
#include "Geometry.h"
class Sphere:public Geometry{
	public:
	Vector3 center;
	float radius;
	Sphere(float radius=1,Vector3 center=Vector3(0,0,0))noexcept:center(center),radius(radius){}
	IntersectInfo testIntersect(Ray r)const noexcept override;
};
#endif //SPHERE_H