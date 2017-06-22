#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include <functional>
#include <random>
#include "Vector3.h"
#include "Ray.h"
#include "Light.h"
class PointLight:public Light{
	public:
	Vector3 intensity;
	Vector3 position;
	PointLight(Vector3 intensity,Vector3 position=Vector3(0,0,0))noexcept:intensity(intensity),position(position){}
	LightReachInfo testReach(Ray r)const noexcept override;
	Vector3 getIntensity(Vector3 position,::std::function<Vector3(Vector3,Vector3)> filter)const noexcept override;
	Photon emit(::std::default_random_engine& gen)const noexcept override;
};
#endif //POINTLIGHT_H