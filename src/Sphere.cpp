#include <cmath>
#include "Geometry.h"
#include "Sphere.h"
#include "Vector3.h"
#include "Ray.h"

IntersectInfo Sphere::testIntersect(Ray r)const noexcept{
	IntersectInfo ii;
	Vector3 rayStartToCenter=this->center-r.start;
	float sqrDistanceToRay=cross(r.getDirection(),rayStartToCenter).sqrLength();
	float sqrRadius=this->radius*this->radius;
	if(sqrDistanceToRay>sqrRadius){
		ii.isIntersect=false;
	}else{
		float centerStep=sqrt(rayStartToCenter.sqrLength()-sqrDistanceToRay);
		float stepOffset=sqrt(sqrRadius-sqrDistanceToRay);
		centerStep*=(dot(r.getDirection(),rayStartToCenter)>0?1:-1);
		if(centerStep+stepOffset<0){
			ii.isIntersect=false;
		}else{
			ii.isIntersect=true;
			if(centerStep-stepOffset<0){
				ii.distance=centerStep+stepOffset;
			}else{
				ii.distance=centerStep-stepOffset;
			}
			ii.pos=ii.distance*r.getDirection()+r.start;
			ii.normal=(ii.pos-this->center).normalized();
		}
	}
	return ii;
}