#ifndef OBJECT_H
#define OBJECT_H
#include "Geometry.h"
#include "Material.h"
struct Object{
	::std::shared_ptr<Geometry> geo;
	::std::shared_ptr<Material> mat;
};
#endif //OBJECT_H