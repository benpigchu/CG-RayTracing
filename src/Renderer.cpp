#include <cstddef>
#include <tuple>
#include <random>
#include "Bitmap.h"
#include "Camera.h"
#include "Scene.h"
#include "HitPointHost.h"
#include "Renderer.h"
#include "Material.h"
#include "Vector3.h"
#include "Ray.h"
#include "Util.h"
#include "RunTask.hpp"

#include <iostream>

void Renderer::rayTracing(Bitmap& bitmap,const Scene& scene,const Camera& camera)noexcept{
	auto renderer=[](Ray r,const Scene& scene){
		Vector3 pixel;
		pixel=Vector3(0,0,0);
		size_t maxDepth=16;
		struct RayTracingTask{
			Ray r;
			Vector3 weight;
			size_t depth;
		};
		RayTracingTask init{r,Vector3(1,1,1),0};
		runTaskFIFO<RayTracingTask>(init,[&pixel,&scene,maxDepth](RayTracingTask task,auto addTask){
			if(task.weight.length()<eps||task.depth>=maxDepth){
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
				auto result=mat->transformRay(task.r,ii.normal,ii.pos,ii.u,ii.v);
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
						RayTracingTask next{nextRay,task.weight.scaled(weight),task.depth+1};
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

const double Renderer::PhotonMappingEngine::ALPHA=0.5;

void Renderer::PhotonMappingEngine::setupHitPoint()noexcept{
	::std::vector<HitPoint> hps;
	auto generateHitPoint=[this,&hps](Ray r,const Scene& scene,ptrdiff_t x,ptrdiff_t y){
		size_t maxDepth=16;
		struct RayTracingTask{
			Ray r;
			Vector3 weight;
			size_t depth;
		};
		RayTracingTask init{r,Vector3(1,1,1),0};
		runTaskFIFO<RayTracingTask>(init,[this,&scene,maxDepth,x,y,&hps](RayTracingTask task,auto addTask){
			if(task.weight.length()<eps||task.depth>=maxDepth){
				return;
			}
			auto iiResult=scene.testIntersect(task.r);
			auto riResult=scene.testLightReach(task.r);
			if(!(iiResult.second.isIntersect)){
				if(!(riResult.second.isReach)){
					return;
				}else{
					this->litHitRecord.push_back(::std::make_tuple(x,y,riResult.second.intensity.scaled(task.weight)));
					return;
				}
			}else{
				if(riResult.second.isReach){
					if(riResult.second.distance<iiResult.second.distance){
						this->litHitRecord.push_back(::std::make_tuple(x,y,riResult.second.intensity.scaled(task.weight)));
						return;
					}
				}
				auto ii=iiResult.second;
				auto mat=iiResult.first;
				auto result=mat->transformRay(task.r,ii.normal,ii.pos,ii.u,ii.v);
				for(auto data:result){
					Vector3 weight=data.weight*data.probablity;
					if(data.isDiffuse){
						HitPoint hp;
						hp.position=ii.pos;
						hp.normal=ii.normal;
						hp.rayDirection=task.r.getDirection();
						hp.imageX=x;
						hp.imageY=y;
						hp.weight=weight.scaled(task.weight);
						hp.radius=this->initRadius;
						hps.push_back(hp);
					}else{
						Ray nextRay=data.newRay;
						nextRay.step(eps);
						RayTracingTask next{nextRay,task.weight.scaled(weight),task.depth+1};
						addTask(next);
					}
				}
			}
		});
	};
	size_t height=this->bitmap.getHeight();
	size_t width=this->bitmap.getWidth();
	for(int i=0;i<width;i++){
		for(int j=0;j<height;j++){
			double x=i+0.5-width/2.0;
			double y=j+0.5-height/2.0;
			generateHitPoint(this->camera.makeRay(x,y),this->scene,i,j);
		}
	}
	this->hpHost.init(hps);
}

void Renderer::PhotonMappingEngine::processPhoton(size_t pass)noexcept{
	auto processPhoton=[this](const Scene& scene){
		auto lights=scene.getLights();
		ptrdiff_t id=::std::uniform_int_distribution<ptrdiff_t>(1,lights.size())(this->ranGen);
		::std::shared_ptr<Light> light;
		for(auto l:lights){
			id--;
			if(id<=0){
				light=l;
				break;
			}
		}
		Photon p=light->emit(this->ranGen);
		p.intensity*=75000;
		p.ray.step(eps);
		size_t maxDepth=16;
		struct RayTracingTask{
			Photon photon;
			size_t depth;
		};
		RayTracingTask init{p,0};
		runTaskFIFO<RayTracingTask>(init,[this,&scene,maxDepth](RayTracingTask task,auto addTask){
			if(task.photon.intensity.length()<eps||task.depth>=maxDepth){
				return;
			}
			auto iiResult=scene.testIntersect(task.photon.ray);
			auto riResult=scene.testLightReach(task.photon.ray);
			if(!(iiResult.second.isIntersect)){
				return;
			}else{
				if(riResult.second.isReach){
					return;
				}
				auto ii=iiResult.second;
				auto mat=iiResult.first;
				auto result=mat->transformRay(task.photon.ray,ii.normal,ii.pos,ii.u,ii.v);
				double select=(::std::uniform_real_distribution<double>(0,1))(this->ranGen);
				for(auto data:result){
					select-=data.probablity;
					if(select>0){
						continue;
					}
					if(data.isDiffuse){
						if(dot(task.photon.ray.getDirection(),ii.normal)>0){
							continue;
						}
						this->hpHost.forEachInSphere(ii.pos,this->initRadius,[ii,task](HitPoint& hp){
							if((ii.pos-hp.position).length()>hp.radius){
								return;
							}
							Vector3 intensity=dot(hp.normal,Vector3(0,0,0)-task.photon.ray.getDirection())*task.photon.intensity;
							hp.intensity+=intensity;
							hp.newPhotonCount++;
						});
					}else{
						Ray nextRay=data.newRay;
						nextRay.step(eps);
						Photon p{nextRay,task.photon.intensity.scaled(data.weight)*data.probablity};
						RayTracingTask next{p,task.depth+1};
						addTask(next);
					}
					break;
				}
			}
		});
	};
	this->photonNum+=pass;
	while(pass>0){
		pass--;
		processPhoton(this->scene);
	}
	this->hpHost.forEach([this](HitPoint& hp){
		if(hp.newPhotonCount>0){
			double coeff=(hp.newPhotonCount*PhotonMappingEngine::ALPHA+hp.photonCount)/(hp.newPhotonCount+hp.photonCount);
			hp.radius*=::std::sqrt(coeff);
			hp.intensity*=coeff;
			hp.photonCount+=hp.newPhotonCount*PhotonMappingEngine::ALPHA;
			hp.newPhotonCount=0;
		}
	});
}

void Renderer::PhotonMappingEngine::writeBitmap()noexcept{
	size_t height=this->bitmap.getHeight();
	size_t width=this->bitmap.getWidth();
	for(int i=0;i<width;i++){
		for(int j=0;j<height;j++){
			this->bitmap.at(i,j)=Vector3(0,0,0);
		}
	}
	for(auto x:this->litHitRecord){
		this->bitmap.at(::std::get<0>(x),::std::get<1>(x))+=::std::get<2>(x);
	}
	this->hpHost.forEach([this](HitPoint hp){
		this->bitmap.at(hp.imageX,hp.imageY)+=hp.intensity.scale(hp.weight)/(/*hp.photonCount+hp.newPhotonCount*/this->photonNum)/(PI*hp.radius*hp.radius);
	});
}