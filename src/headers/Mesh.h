#ifndef MESH_H
#define MESH_H
#include <cstddef>
#include <vector>
#include <istream>
#include <ostream>
#include "Vector3.h"
#include "BezierCurve.h"

struct Vertex{
	Vector3 pos;
};

struct Face{
	ptrdiff_t i[3];
};

struct Mesh{
	::std::vector<Vertex> vertices;
	::std::vector<Face> faces;
	static Mesh importFromOBJ(::std::istream& is)noexcept;
	static Mesh generateRotationFromBezier(BezierCurve bc,size_t tSample,size_t sSample)noexcept;
	void exportAsOBJ(::std::ostream& os)const noexcept;
};

#endif //MESH_H