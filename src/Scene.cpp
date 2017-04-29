#include <memory>
#include <utility>
#include "Scene.h"
#include "Geometry.h"
#include "Material.h"
#include "Object.h"
#include "Ray.h"

::std::pair<::std::shared_ptr<Material>,IntersectInfo> Scene::testIntersect(Ray r)const noexcept{
	IntersectInfo ii;
	::std::shared_ptr<Material> mat;
	ii.isIntersect=false;
	for(::std::shared_ptr<Object> object:this->objects){
		IntersectInfo newii=object->testIntersect(r);
		if(newii.isIntersect){
			if(!ii.isIntersect){
				ii=newii;
				mat=object->material;
			}else{
				if(newii.distance<ii.distance){
					ii=newii;
					mat=object->material;
				}
			}
		}
	}
	return ::std::make_pair(mat,ii);
}

::std::pair<::std::shared_ptr<Light>,LightReachInfo> Scene::testLightReach(Ray r)const noexcept{
	LightReachInfo lri;
	::std::shared_ptr<Light> lit;
	lri.isReach=false;
	for(::std::shared_ptr<Light> light:this->lights){
		LightReachInfo newlri=light->testReach(r);
		if(newlri.isReach){
			if(!lri.isReach){
				lri=newlri;
				lit=light;
			}else{
				if(newlri.distance<lri.distance){
					lri=newlri;
					lit=light;
				}
			}
		}
	}
	return ::std::make_pair(lit,lri);
}