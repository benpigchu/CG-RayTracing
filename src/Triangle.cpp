#include "Geometry.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "Ray.h"
#include "Triangle.h"

IntersectInfo Triangle::testIntersect(Ray r)const noexcept{
	// x+dt=au+bv+cw
	// a+b+c=1
	// [M4x4][a,b,c,d]T=[...x,1]
	IntersectInfo ii;
	Vector3 t=r.getDirection();
	Vector3 u=this->point[0];
	Vector3 v=this->point[1];
	Vector3 w=this->point[2];
	Matrix4 factor(u.x,v.x,w.x,-t.x,u.y,v.y,w.y,-t.y,u.z,v.z,w.z,-t.z,1,1,1,0);
	double a=r.start.x,b=r.start.y,c=r.start.z,d=1;
	if(factor.determinant()==0){
		ii.isIntersect=false;
		return ii;
	}
	applyTo(factor.inverse(),a,b,c,d);
	if(d>0&&c>0&&b>0&&a>0){
		ii.isIntersect=true;
		ii.distance=d;
		ii.pos=r.start+d*t;
		ii.normal=this->nm;
	}else{
		ii.isIntersect=false;
	}
	return ii;
}