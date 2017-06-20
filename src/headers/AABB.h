#ifndef AABB_H
#define AABB_H
#include <cmath>
#include "Vector3.h"
#include "Ray.h"

struct AABBIntersectInfo{
	bool isIntersect;
	double near,far;
	friend inline ::std::ostream& operator<<(::std::ostream& os,const AABBIntersectInfo& ii)noexcept{
		if(ii.isIntersect){
			os<<"(Intersected near:"<<ii.near<<" far:"<<ii.far<<")";
		}else{
			os<<"(Not Intersected)";
		}
		return os;
	}
};

// Axis-aligned bounding box
struct AABB{
	Vector3 min,max;
	AABB(Vector3 min,Vector3 max)noexcept:min(min),max(max){}
	inline double getDistance(Vector3 v){
		double xdis=(::std::abs(this->max.x-v.x)+::std::abs(v.x-this->min.x)-::std::abs(this->min.x-this->max.x))/2;
		double ydis=(::std::abs(this->max.y-v.y)+::std::abs(v.y-this->min.y)-::std::abs(this->min.y-this->max.y))/2;
		double zdis=(::std::abs(this->max.z-v.z)+::std::abs(v.z-this->min.z)-::std::abs(this->min.z-this->max.z))/2;
		return ::std::sqrt(xdis*xdis+ydis*ydis+zdis*zdis);
	}
	AABBIntersectInfo testIntersect(Ray r)noexcept;
	friend inline ::std::ostream& operator<<(::std::ostream& os,const AABB& aabb)noexcept{
		os<<"(AABB min:"<<aabb.min<<" max:"<<aabb.max<<")";
		return os;
	}
};

#endif //AABB_H