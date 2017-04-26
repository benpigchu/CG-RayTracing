#include <memory>
#include <utility>
#include "Scene.h"
#include "Geometry.h"
#include "Material.h"
#include "Object.h"
#include "Ray.h"

::std::pair<::std::weak_ptr<Material>,IntersectInfo> Scene::testIntersect(Ray r)const noexcept{
	IntersectInfo ii;
	::std::weak_ptr<Material> mat;
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