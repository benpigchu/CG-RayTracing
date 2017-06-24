#ifndef WEIGHTTEXTUREDMATERIAL_H
#define WEIGHTTEXTUREDMATERIAL_H
#include <vector>
#include <memory>
#include "Vector3.h"
#include "Bitmap.h"
#include "Ray.h"
#include "Material.h"

class WeightTexturedMaterial:public Material{
	public:
	Bitmap texture;
	::std::shared_ptr<Material> material;
	WeightTexturedMaterial(Bitmap texture,::std::shared_ptr<Material> material)noexcept:texture(texture),material(material){}
	::std::vector<TransformedRayData> transformRay(Ray r,Vector3 normal,Vector3 pos,double u,double v)const noexcept override;
};

#endif //WEIGHTTEXTUREDMATERIAL_H