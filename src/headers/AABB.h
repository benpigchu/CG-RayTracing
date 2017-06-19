#ifndef AABB_H
#define AABB_H
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
	AABBIntersectInfo testIntersect(Ray r)noexcept;
	friend inline ::std::ostream& operator<<(::std::ostream& os,const AABB& aabb)noexcept{
		os<<"(AABB min:"<<aabb.min<<" max:"<<aabb.max<<")";
		return os;
	}
};

#endif //AABB_H