#include <vector>
#include <memory>
#include "Vector3.h"
#include "Bitmap.h"
#include "Ray.h"
#include "Material.h"
#include "WeightTexturedMaterial.h"

::std::vector<TransformedRayData> WeightTexturedMaterial::transformRay(Ray r,Vector3 normal,Vector3 pos,double u,double v)const noexcept{
	Vector3 modifier=this->texture.sample(u,v);
	auto result=this->material->transformRay(r,normal,pos,u,v);
	for(TransformedRayData& data:result){
		data.weight.scale(modifier);
	}
	return result;
}
