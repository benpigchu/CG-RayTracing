#ifndef MESHGEOMETRY_H
#define MESHGEOMETRY_H
#include <vector>
#include "Geometry.h"
#include "Vector3.h"
#include "Ray.h"
#include "Mesh.h"
#include "Triangle.h"
#include "MeshIntersectOptimiser.h"

class MeshGeometry:public Geometry{
	static const bool USE_KDTREE_OPTIMISE=true;
	MeshIntersectOptimiser kdTree;
	::std::vector<Triangle> triangles;
	public:
	MeshGeometry(Mesh mesh,Vector3 scale=Vector3(1,1,1))noexcept{
		setMesh(mesh,scale);
	}
	void setMesh(Mesh mesh,Vector3 scale)noexcept;
	IntersectInfo testIntersect(Ray r)const noexcept;
};

#endif //MESHGEOMETRY_H