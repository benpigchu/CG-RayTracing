#ifndef HITPOINTHOST_H
#define HITPOINTHOST_H
#include <cstddef>
#include <functional>
#include "Vector3.h"
#include "AABB.h"
#include "KDTree.hpp"

struct HitPoint{
	Vector3 position;
	Vector3 normal;
	Vector3 rayDirection;
	ptrdiff_t imageX,imageY;
	Vector3 weight;
	double radius;
	Vector3 intensity=Vector3(0,0,0);
	double photonCount=0;
	double newPhotonCount=0;
};

class HitPointHost:public KDTree<HitPoint>{
	protected:
	AABB getAABB(HitPoint d)const noexcept override;
	void processNode(Node& node)const noexcept override;
	public:
	// Don't modify position in forEach
	void forEach(::std::function<void(HitPoint&)> func)noexcept;
	void forEachInSphere(Vector3 pos,double radius,::std::function<void(HitPoint&)> func)noexcept;
};


#endif //HITPOINTHOST_H