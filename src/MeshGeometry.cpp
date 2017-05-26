#include <vector>
#include "Vector3.h"
#include "Matrix4.h"
#include "Geometry.h"
#include "Mesh.h"
#include "MeshGeometry.h"

#include <iostream>


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

void MeshGeometry::setMesh(Mesh mesh,Vector3 scale)noexcept{
	this->triangles.clear();
	for(Face f:mesh.faces){
		Triangle tri;
		tri.point[0]=mesh.vertices[f.i[0]].pos.scaled(scale);
		tri.point[1]=mesh.vertices[f.i[1]].pos.scaled(scale);
		tri.point[2]=mesh.vertices[f.i[2]].pos.scaled(scale);
		tri.nm=cross(tri.point[1]-tri.point[0],tri.point[2]-tri.point[1]).normalize();
		this->triangles.push_back(tri);
	}
}

IntersectInfo MeshGeometry::testIntersect(Ray r)const noexcept{
	IntersectInfo ii;
	ii.isIntersect=false;
	for(Triangle tri:this->triangles){
		IntersectInfo newii=tri.testIntersect(r);
		if(newii.isIntersect){
			if(!ii.isIntersect){
				ii=newii;
			}else{
				if(ii.distance>newii.distance){
					ii=newii;
				}
			}
		}
	}
	return ii;
}