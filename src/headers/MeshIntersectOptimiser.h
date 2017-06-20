#ifndef MESHINTERSECTOPTIMISER_H
#define MESHINTERSECTOPTIMISER_H
#include "KDTree.hpp"
#include "Geometry.h"
#include "Triangle.h"

class MeshIntersectOptimiser:KDTree<Triangle>{
	AABB getAABB(Triangle d)const noexcept override;
	void processNode(Node& node)const noexcept override;
	IntersectInfo testIntersect(Ray r)const noexcept;
};

#endif //MESHINTERSECTOPTIMISER_H