#ifndef OBJECT_H
#define OBJECT_H
#include <memory>
#include "Ray.h"
#include "Geometry.h"
#include "Material.h"
#include "Transform.h"

struct Object{
	::std::shared_ptr<Geometry> geometry;
	::std::shared_ptr<Material> material;
	Transform transform;
	IntersectInfo testIntersect(Ray r)const noexcept;
};
#endif //OBJECT_H