#include <cmath>
#include "PointLight.h"
#include "Vector3.h"
#include "Ray.h"
#include "Light.h"
#include "Util.h"

LightReachInfo PointLight::testReach(Ray r)const noexcept{
	LightReachInfo lri;
	Vector3 rayStartToCenter=this->position-r.start;
	double distanceToRay=cross(r.getDirection(),rayStartToCenter).length();
	if(distanceToRay<eps&&dot(r.getDirection(),rayStartToCenter)>0){
		lri.isReach=true;
		lri.distance=rayStartToCenter.length();
		lri.intensity=this->intensity;
	}else{
		lri.isReach=false;
	}
	return lri;
}

Vector3 PointLight::getIntensity(Vector3 position,::std::function<Vector3(Vector3,Vector3)> filter)const noexcept{
	return filter(this->intensity,this->position);
}