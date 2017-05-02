#include "Vector3.h"
#include "Ray.h"
#include "Material.h"
#include "DiffuseMaterial.h"

::std::vector<TransformedRayData> DiffuseMaterial::transformRay(Ray r,Vector3 normal,Vector3 pos)const noexcept{
	::std::vector<TransformedRayData> result(1);
	result[0].isDiffuse=true;
	result[0].weight=this->color;
	result[0].probablity=1;
	return result;
}
