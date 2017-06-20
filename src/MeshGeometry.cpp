#include <vector>
#include "Vector3.h"
#include "Matrix4.h"
#include "Geometry.h"
#include "Mesh.h"
#include "MeshGeometry.h"

#include <iostream>

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