#ifndef HITPOINTHOST_H
#define HITPOINTHOST_H
#include<cstddef>
#include "Vector3.h"

struct HitPoint{
	Vector3 position;
	Vector3 normal;
	Vector3 rayDirection;
	Vector3 rayDirection;
	ptrdiff_t imageX,imageY;
	Vector3 weight;
};


#endif //HITPOINTHOST_H