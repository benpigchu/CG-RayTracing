#ifndef MATERIAL_H
#define MATERIAL_H
#include <vector>
#include <ostream>
#include "Vector3.h"
#include "Ray.h"

struct TransformedRayData{
	bool isDiffuse;
	Ray newRay;
	Vector3 weight;
	double probablity;
	friend inline ::std::ostream& operator<<(::std::ostream& os,const TransformedRayData& trd)noexcept{
		os<<"(TransformedRayData prob:"<<trd.probablity<<" weight:"<<trd.weight;
		if(trd.isDiffuse){
			os<<" Diffuse)";
		}else{
			os<<" ray:"<<trd.newRay<<")";
		}
		return os;
	}
};

class Material{
	public:
	virtual ::std::vector<TransformedRayData> transformRay(Ray r,Vector3 normal,Vector3 pos,double u,double v)const noexcept = 0;
};

#endif //MATERIAL_H