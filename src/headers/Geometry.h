#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <ostream>
#include "Ray.h"
#include "Vector3.h"

struct IntersectInfo{
	bool isIntersect;
	Vector3 pos;
	Vector3 normal;
	double distance;
	friend inline ::std::ostream& operator<<(::std::ostream& os,const IntersectInfo& ii)noexcept{
		if(ii.isIntersect){
			os<<"(Intersected at "<<ii.pos<<" d:"<<ii.distance<<" nm:"<<ii.normal<<")";
		}else{
			os<<"(Not Intersected)";
		}
		return os;
	}
};

class Geometry{
	public:
	virtual IntersectInfo testIntersect(Ray r)const noexcept = 0;
};
#endif //GEOMETRY_H