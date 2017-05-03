#ifndef SQUARELIGHT_H
#define SQUARELIGHT_H
#include <cstddef>
#include "Vector3.h"
#include "Transform.h"
#include "Square.h"
#include "Ray.h"
#include "Light.h"
class SquareLight:public Light{
	public:
	Vector3 intensity;
	Transform transform;
	Square square;
	SquareLight(Vector3 intensity,double side,Transform transform=Transform())noexcept:intensity(intensity),square(Square(side)),transform(transform){}
	LightReachInfo testReach(Ray r)const noexcept override;
	Vector3 getIntensity(Vector3 position,::std::function<Vector3(Vector3,Vector3)> filter)const noexcept override;
};
#endif //SQUARELIGHT_H