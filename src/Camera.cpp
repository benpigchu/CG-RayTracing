#include <cstddef>
#include <set>
#include <memory>
#include "Camera.h"
#include "Bitmap.h"
#include "Scene.h"
#include "Material.h"
#include "vector3.h"
#include "Ray.h"
#include "Util.h"
#include "RunTask.hpp"

#include <iostream>

void Camera::render(Bitmap& bitmap,const Scene& scene)noexcept{
	size_t height=bitmap.getHeight();
	size_t width=bitmap.getWidth();
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			double x=i+0.5-width/2.0;
			double y=j+0.5-height/2.0;
			Vector3& pixel=bitmap.at(i,j);
			pixel=Vector3(0,0,0);
			struct RayTracingTask{
				Ray r;
				Vector3 weight;
			};
			RayTracingTask init{this->makeRay(x,y),Vector3(1,1,1)};
			runTask<RayTracingTask>(init,[&pixel,&scene](RayTracingTask task,auto addTask){
				auto iiResult=scene.testIntersect(task.r);
				auto riResult=scene.testLightReach(task.r);
				if(!(iiResult.second.isIntersect)){
					if(!(riResult.second.isReach)){
						return;
					}else{
						pixel.r+=riResult.second.intensity.r*task.weight.r;
						pixel.g+=riResult.second.intensity.g*task.weight.g;
						pixel.b+=riResult.second.intensity.b*task.weight.b;
						return;
					}
				}else{
					if(riResult.second.isReach){
						if(riResult.second.distance<iiResult.second.distance){
							pixel.r+=riResult.second.intensity.r*task.weight.r;
							pixel.g+=riResult.second.intensity.g*task.weight.g;
							pixel.b+=riResult.second.intensity.b*task.weight.b;
							return;
						}
					}
					auto ii=iiResult.second;
					auto mat=iiResult.first;
					auto result=mat->transformRay(task.r,ii.normal,ii.pos);
					//temp
					Vector3 weight=result[0].weight;
					for(const ::std::shared_ptr<Light>& light:scene.getLights()){
						Vector3 intensity=light->getIntensity(ii.pos,[task,ii,scene](Vector3 intensity,Vector3 originPosition){
							Vector3 toLight=(originPosition-ii.pos).normalized();
							Ray r(toLight,ii.pos);
							r.step(eps);
							if(scene.testIntersect(r).second.isIntersect){
								return Vector3(0,0,0);
							}
							return dot(ii.normal,toLight)*intensity;
						});
						pixel.r+=intensity.r*task.weight.r*weight.r;
						pixel.g+=intensity.g*task.weight.g*weight.g;
						pixel.b+=intensity.b*task.weight.b*weight.b;
					}
				}
			});
		}
	}
}