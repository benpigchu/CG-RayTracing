#ifndef MIRRORMATERIAL_H
#define MIRRORMATERIAL_H
#include <vector>
#include "Vector3.h"
#include "Ray.h"
#include "Material.h"

class MirrorMaterial:public Material{
	public:
	Vector3 color;
	MirrorMaterial(Vector3 color)noexcept:color(color){}
	::std::vector<TransformedRayData> transformRay(Ray r,Vector3 normal,Vector3 pos,double u,double v)const noexcept override;
};

#endif //MIRRORMATERIAL_H