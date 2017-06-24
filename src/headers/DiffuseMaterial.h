#ifndef DIFFUSEMATERIAL_H
#define DIFFUSEMATERIAL_H
#include <vector>
#include "Vector3.h"
#include "Ray.h"
#include "Material.h"

class DiffuseMaterial:public Material{
	public:
	Vector3 color;
	DiffuseMaterial(Vector3 color)noexcept:color(color){}
	::std::vector<TransformedRayData> transformRay(Ray r,Vector3 normal,Vector3 pos,double u,double v)const noexcept override;
};

#endif //DIFFUSEMATERIAL_H