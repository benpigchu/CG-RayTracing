#ifndef MESHGEOMETRY_H
#define MESHGEOMETRY_H
#include <vector>
#include "Geometry.h"
#include "Vector3.h"
#include "Mesh.h"

struct Triangle{
	Vector3 nm;
	Vector3 point[3];
	IntersectInfo testIntersect(Ray r)const noexcept;
};

class MeshGeometry:public Geometry{
	::std::vector<Triangle> triangles;
	public:
	MeshGeometry(Mesh mesh,Vector3 scale=Vector3(1,1,1))noexcept{
		setMesh(mesh,scale);
	}
	void setMesh(Mesh mesh,Vector3 scale)noexcept;
	IntersectInfo testIntersect(Ray r)const noexcept;
};

#endif //MESHGEOMETRY_H