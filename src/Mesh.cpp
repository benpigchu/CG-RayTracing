#include <cstddef>
#include <cmath>
#include <vector>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>
#include "Util.h"
#include "Mesh.h"
#include "Vector3.h"

Mesh Mesh::importFromOBJ(::std::istream& is)noexcept{
	Mesh m;
	while(is){
		::std::string tmp;
		::std::getline(is,tmp);
		if(tmp[0]=='#'){
			continue;
		}
		::std::istringstream lineIn(tmp);
		lineIn>>tmp;
		if(tmp=="v"){
			Vertex v;
			lineIn>>v.pos.x>>v.pos.y>>v.pos.z;
			m.vertices.push_back(v);
			continue;
		}
		if(tmp=="f"){
			Face f;
			lineIn>>f.i[0]>>f.i[1]>>f.i[2];
			f.i[0]-=1;
			f.i[1]-=1;
			f.i[2]-=1;
			m.faces.push_back(f);
			continue;
		}
	}
	return m;
}

Mesh Mesh::generateRotationFromBezier(BezierCurve bc,size_t tSample,size_t sSample)noexcept{
	Mesh m;
	for(ptrdiff_t t=0;t<=tSample;t++){
		auto bezierPoint=bc.getPoint(((double)t)/((double)tSample));
		for(ptrdiff_t s=0;s<sSample;s++){
			Vertex v;
			double arg=2*PI*s/sSample;
			v.pos.x=bezierPoint.first*::std::cos(arg);
			v.pos.y=bezierPoint.second;
			v.pos.z=bezierPoint.first*::std::sin(arg);
			m.vertices.push_back(v);
		}
	}
	for(ptrdiff_t t=0;t<tSample;t++){
		for(ptrdiff_t s=0;s<sSample;s++){
			Face f1,f2;
			f1.i[0]=t*sSample+((s+1)%sSample);
			f1.i[1]=t*sSample+s;
			f1.i[2]=(t+1)*sSample+s;
			f2.i[0]=(t+1)*sSample+s;
			f2.i[1]=(t+1)*sSample+((s+1)%sSample);
			f2.i[2]=t*sSample+((s+1)%sSample);
			m.faces.push_back(f1);
			m.faces.push_back(f2);
		}
	}
	return m;
};

void Mesh::exportAsOBJ(::std::ostream& os)const noexcept{
	for(Vertex v:this->vertices){
		os<<"v "<<v.pos.x<<" "<<v.pos.y<<" "<<v.pos.z<<"\n";
	}
	for(Face f:this->faces){
		os<<"f "<<f.i[0]+1<<" "<<f.i[1]+1<<" "<<f.i[2]+1<<"\n";
	}
}