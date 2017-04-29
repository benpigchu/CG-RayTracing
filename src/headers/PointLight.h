#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "Vector3.h"
#include "Ray.h"
#include "Light.h"
class PointLight:public Light{
	public:
	Vector3 intensity;
	Vector3 position;
	PointLight(Vector3 intensity,Vector3 position=Vector3(0,0,0))noexcept:intensity(intensity),position(position){}
	LightReachInfo testReach(Ray r)const noexcept override;
};

#endif //POINTLIGHT_H