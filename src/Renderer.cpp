#include "Bitmap.h"
#include "Camera.h"
#include "Scene.h"
#include "Renderer.h"
#include "Material.h"
#include "vector3.h"
#include "Ray.h"
#include "Util.h"
#include "RunTask.hpp"

#include <iostream>

void Renderer::rayTracing(Bitmap& bitmap,const Scene& scene,const Camera& camera)noexcept{
	auto renderer=[](Ray r,const Scene& scene){
		Vector3 pixel;
		pixel=Vector3(0,0,0);
		struct RayTracingTask{
			Ray r;
			Vector3 weight;
		};
		RayTracingTask init{r,Vector3(1,1,1)};
		runTask<RayTracingTask>(init,[&pixel,&scene](RayTracingTask task,auto addTask){
			if(task.weight.length()<eps){
				return;
			}
			auto iiResult=scene.testIntersect(task.r);
			auto riResult=scene.testLightReach(task.r);
			if(!(iiResult.second.isIntersect)){
				if(!(riResult.second.isReach)){
					return;
				}else{
					pixel+=riResult.second.intensity.scaled(task.weight);
					return;
				}
			}else{
				if(riResult.second.isReach){
					if(riResult.second.distance<iiResult.second.distance){
						pixel+=riResult.second.intensity.scaled(task.weight);
						return;
					}
				}
				auto ii=iiResult.second;
				auto mat=iiResult.first;
				auto result=mat->transformRay(task.r,ii.normal,ii.pos);
				for(auto data:result){
					Vector3 weight=data.weight*data.probablity;
					if(data.isDiffuse){
						for(const ::std::shared_ptr<Light>& light:scene.getLights()){
							Vector3 intensity=light->getIntensity(ii.pos,[task,ii,scene](Vector3 intensity,Vector3 originPosition){
								Vector3 fromLight=(ii.pos-originPosition).normalized();
								double distance=(originPosition-ii.pos).length();
								Ray r(fromLight,originPosition);
								r.step(-eps);
								auto test=scene.testIntersect(r).second;
								if(test.isIntersect&&test.distance<distance){
									return Vector3(0,0,0);
								}
								return dot(ii.normal,Vector3(0,0,0)-fromLight)*intensity;
							});
							pixel+=intensity.scaled(task.weight).scaled(weight);
						}
					}else{
						Ray nextRay=data.newRay;
						nextRay.step(eps);
						RayTracingTask next{nextRay,task.weight.scaled(weight)};
						addTask(next);
					}
				}
			}
		});
		return pixel;
	};
	size_t height=bitmap.getHeight();
	size_t width=bitmap.getWidth();
	for(int i=0;i<width;i++){
		for(int j=0;j<height;j++){
			double x=i+0.5-width/2.0;
			double y=j+0.5-height/2.0;
			Vector3& pixel=bitmap.at(i,j);
			pixel=renderer(camera.makeRay(x,y),scene);
		}
		::std::cout<<"rendering... ["<<i<<"]"<<::std::endl;
	}
}