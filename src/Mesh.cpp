#include <cstddef>
#include <vector>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>
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
void Mesh::exportAsOBJ(::std::ostream& os)const noexcept{
	for(Vertex v:this->vertices){
		os<<"v "<<v.pos.x<<" "<<v.pos.y<<" "<<v.pos.z<<"\n";
	}
	for(Face f:this->faces){
		os<<"f "<<f.i[0]+1<<" "<<f.i[1]+1<<" "<<f.i[2]+1<<"\n";
	}
}