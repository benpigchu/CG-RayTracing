#include <cmath>
#include "Geometry.h"
#include "Square.h"
#include "Vector3.h"
#include "Ray.h"

IntersectInfo Square::testIntersect(Ray r)const noexcept{
	IntersectInfo ii;
	if(r.start.z<0&&r.getDirection().z<0){
		ii.isIntersect=false;
	}else if(r.start.z>0&&r.getDirection().z>0){
		ii.isIntersect=false;
	}else{
		ii.distance=-r.start.z/r.getDirection().z;
		r.step(-r.start.z/r.getDirection().z);
		float x=r.start.x;
		float y=r.start.y;
		if(x>this->side||x<-this->side||y>this->side||y<-this->side){
			ii.isIntersect=false;
		}else{
			ii.u=(x+this->side)/(2*this->side);
			ii.v=(y+this->side)/(2*this->side);
			ii.isIntersect=true;
			ii.pos=r.start;
			ii.normal=Vector3(0,0,-1);
		}
	}
	return ii;
}