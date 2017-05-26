#ifndef MESHGEOMETRY_H
#define MESHGEOMETRY_H
#include <vector>
#include "Geometry.h"
#include "Mesh.h"

struct Triangle{
	Vector3 nm;
	Vector3 point[3];
	IntersectInfo testIntersect(Ray r)const noexcept;
};

class MeshGeometry:public Geometry{
	::std::vector<Triangle> triangles;
	public:
	MeshGeometry(Mesh mesh)noexcept{
		setMesh(mesh);
	}
	void setMesh(Mesh mesh)noexcept;
	IntersectInfo testIntersect(Ray r)const noexcept;
};

#endif //MESHGEOMETRY_H