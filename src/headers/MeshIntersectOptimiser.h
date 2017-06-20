#ifndef MESHINTERSECTOPTIMISER_H
#define MESHINTERSECTOPTIMISER_H
#include <vector>
#include "KDTree.hpp"
#include "Geometry.h"
#include "Triangle.h"

class MeshIntersectOptimiser:public KDTree<Triangle>{
	protected:
	AABB getAABB(Triangle d)const noexcept override;
	void processNode(Node& node)const noexcept override;
	public:
	IntersectInfo testIntersect(Ray r)const noexcept;
};

#endif //MESHINTERSECTOPTIMISER_H