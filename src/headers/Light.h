#ifndef LIGHT_H
#define LIGHT_H
#include <ostream>
#include <functional>
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
	virtual Vector3 getIntensity(Vector3 position,::std::function<Vector3(Vector3,Vector3)> filter)const noexcept = 0;
	// we may use mutli-sample to decide the intensity to the surface, use resultIntensity filter(intensity,originPosition) to get your intensity
};

#endif //LIGHT_H