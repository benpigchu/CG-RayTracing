#ifndef LIGHT_H
#define LIGHT_H
#include "Vector3.h"
#include "Ray.h"

struct LightReachInfo{
	bool isReach;
	float distance;
	Vector3 intensity;
	friend inline ::std::ostream& operator<<(::std::ostream& os,const LightReachInfo& lri)noexcept{
		if(lri.isReach){
			os<<"(Reached light at distance "<<lri.distance<<" i:"<<lri.intensity<<")";
		}else{
			os<<"(Not Reached light)";
		}
		return os;
	}
};

class Light{
	public:
	virtual LightReachInfo testReach(Ray r)const noexcept = 0;
};

#endif //LIGHT_H