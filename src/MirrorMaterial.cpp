#include "Vector3.h"
#include "Ray.h"
#include "Material.h"
#include "MirrorMaterial.h"

::std::vector<TransformedRayData> MirrorMaterial::transformRay(Ray r,Vector3 normal,Vector3 pos,double u,double v)const noexcept{
	::std::vector<TransformedRayData> result(1);
	result[0].isDiffuse=false;
	result[0].probablity=1;
	result[0].weight=this->color;
	Vector3 newDirection=r.getDirection()-2*dot(r.getDirection(),normal)*normal;
	result[0].newRay=Ray(newDirection,pos);
	return result;
}