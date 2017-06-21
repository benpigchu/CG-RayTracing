#include <cmath>
#include <vector>
#include "Vector3.h"
#include "Ray.h"
#include "Material.h"
#include "GlassMaterial.h"

#include <iostream>

::std::vector<TransformedRayData> GlassMaterial::transformRay(Ray r,Vector3 normal,Vector3 pos)const noexcept{
	TransformedRayData reflect;
	TransformedRayData refract;
	double drdotnm=dot(r.getDirection(),normal);
	reflect.isDiffuse=false;
	reflect.probablity=1;
	reflect.weight=this->color;
	Vector3 newReflectDirection=r.getDirection()-2*drdotnm*normal;
	reflect.newRay=Ray(newReflectDirection,pos);
	double n=(drdotnm>0)?this->index:1/this->index;
	double newdrdotnmsqr=1-n*n*(1-drdotnm*drdotnm);
	if(newdrdotnmsqr<0){
		return ::std::vector<TransformedRayData>{reflect};
	}
	double newdrdotnm=::std::sqrt(newdrdotnmsqr)*(drdotnm<0?1:-1);
	refract.isDiffuse=false;
	refract.weight=this->color;
	Vector3 newRefractDirection=n*r.getDirection()-(newdrdotnm+n*drdotnm)*normal;
	::std::cout<<" "<<drdotnm<<" "<<newdrdotnmsqr<<" "<<newRefractDirection;
	refract.newRay=Ray(newRefractDirection,pos);
	double rOrth=(-n*drdotnm-newdrdotnm)/(-n*drdotnm+newdrdotnm);
	double rPar=(-drdotnm-n*newdrdotnm)/(-drdotnm+n*newdrdotnm);
	reflect.probablity=(rOrth*rOrth+rPar*rPar)/2;
	refract.probablity=1-reflect.probablity;
	return ::std::vector<TransformedRayData>{reflect,refract};
}
