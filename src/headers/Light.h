#ifndef LIGHT_H
#define LIGHT_H
#include <ostream>
#include <functional>
#include <random>
#include "Vector3.h"
#include "Ray.h"

struct LightReachInfo{
	bool isReach;
	double distance;
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

struct Photon{
	Ray ray;
	Vector3 intensity;
};

class Light{
	public:
	virtual LightReachInfo testReach(Ray r)const noexcept = 0;
	// we may use mutli-sample to decide the intensity to the surface, use resultIntensity filter(intensity,originPosition) to get your intensity
	virtual Vector3 getIntensity(Vector3 position,::std::function<Vector3(Vector3,Vector3)> filter)const noexcept = 0;
	//emit photon for ppm
	virtual Photon emit(::std::default_random_engine& gen)const noexcept = 0;
};

#endif //LIGHT_H