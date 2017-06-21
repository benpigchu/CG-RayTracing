#ifndef GLASSMATERIAL_H
#define GLASSMATERIAL_H
#include <vector>
#include "Vector3.h"
#include "Ray.h"
#include "Material.h"

class GlassMaterial:public Material{
	public:
	Vector3 color;
	double index;
	GlassMaterial(double index,Vector3 color)noexcept:index(index),color(color){}
	::std::vector<TransformedRayData> transformRay(Ray r,Vector3 normal,Vector3 pos)const noexcept override;
};

#endif //GLASSMATERIAL_H