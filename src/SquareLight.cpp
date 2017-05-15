#include <cmath>
#include "SquareLight.h"
#include "Vector3.h"
#include "Ray.h"
#include "Light.h"
#include "Util.h"

LightReachInfo SquareLight::testReach(Ray r)const noexcept{
	LightReachInfo lri;
	Ray rayBeforeTransform=Ray(apply(this->transform.getRotation().conjugated(),r.getDirection()),apply(this->transform.getMatrixInversed(),r.start));
	IntersectInfo ii=this->square.testIntersect(rayBeforeTransform);
	lri.isReach=ii.isIntersect;
	lri.distance=ii.distance;
	lri.intensity=(dot(r.getDirection(),apply(this->transform.getRotation(),ii.normal))>0)?Vector3(0,0,0):this->intensity;
	return lri;
}

Vector3 SquareLight::getIntensity(Vector3 position,::std::function<Vector3(Vector3,Vector3)> filter)const noexcept{
	if(apply(this->transform.getMatrixInversed(),position).z<0){
		return Vector3(0,0,0);
	}else{
		Vector3 samples;
		int sampleNum=this->square.side*3;
		double unit=this->square.side/2/sampleNum;
		for(int i=-sampleNum;i<sampleNum;i++){
			for(int j=-sampleNum;j<sampleNum;j++){
				Vector3 pos=apply(this->transform.getMatrix(),Vector3((i+0.5)*unit,(j+0.5)*unit,0));
				samples+=filter(this->intensity,pos);
			}
		}
		return samples/4/sampleNum/sampleNum;
	}
}