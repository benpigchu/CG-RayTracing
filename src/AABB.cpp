#include <algorithm>
#include "Vector3.h"
#include "Ray.h"
#include "AABB.h"

AABBIntersectInfo AABB::testIntersect(Ray r)noexcept{
	AABBIntersectInfo aabbii;
	Vector3 direction=r.getDirection();
	double dx=1/direction.x;
	double dy=1/direction.y;
	double dz=1/direction.z;
	double xmind=(this->min.x-r.start.x)*dx;
	double ymind=(this->min.y-r.start.y)*dy;
	double zmind=(this->min.z-r.start.z)*dz;
	double xmaxd=(this->max.x-r.start.x)*dx;
	double ymaxd=(this->max.y-r.start.y)*dy;
	double zmaxd=(this->max.z-r.start.z)*dz;
	if(xmind>xmaxd){
		::std::swap(xmind,xmaxd);
	}
	if(ymind>ymaxd){
		::std::swap(ymind,ymaxd);
	}
	if(zmind>zmaxd){
		::std::swap(zmind,zmaxd);
	}
	aabbii.near=::std::max(::std::max(xmind,ymind),zmind);
	aabbii.far=::std::min(::std::min(xmaxd,ymaxd),zmaxd);
	aabbii.isIntersect=aabbii.near<aabbii.far;
	return aabbii;
}