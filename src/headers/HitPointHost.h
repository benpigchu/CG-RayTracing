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
	size_t photonCount;
	size_t newPhotonCount;
};

class HitPointHost:public KDTree<HitPoint>{
	protected:
	AABB getAABB(HitPoint d)const noexcept override;
	void processNode(Node& node)const noexcept override;
};


#endif //HITPOINTHOST_H