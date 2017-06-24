#include <ostream>
#include <istream>
#include <cmath>
#include <cctype>
#include <stdexcept>
#include "Vector3.h"
#include "Bitmap.h"

void Bitmap::exportAsPPM(::std::ostream& os,double gamma)const noexcept{
	auto printFloat=[&os,gamma](double f){
		double gammaedF=pow(f,1.0/gamma);
		if(gammaedF>1.0f){
			gammaedF=1.0f;
		}
		if(gammaedF<0.0f){
			gammaedF=0.0f;
		}
		os<<static_cast<unsigned char>(gammaedF*255.0+0.5);
	};
	os<<"P6 "<<this->width<<" "<<this->height<<" 255\n";
	for(const Vector3 v:this->data){
		printFloat(v.r);
		printFloat(v.g);
		printFloat(v.b);
	}
}


Bitmap Bitmap::importFromPPM(::std::istream& is,double gamma){
	auto error=::std::runtime_error("invalid ppm file");
	if(is.get()!='P'){
		throw error;
	}
	if(is.get()!='6'){
		throw error;
	}
	if(!::std::isspace(is.get())){
		throw error;
	}
	size_t width,height,colorNum;
	is>>width>>height>>colorNum;
	if(!is){
		throw error;
	}
	if(colorNum!=255){
		throw error;
	}
	Bitmap b(width,height);
	if(!::std::isspace(is.get())){
		throw error;
	}
	for(Vector3& v:b.data){
		v.r=pow((is.get()/255.0),gamma);
		v.g=pow((is.get()/255.0),gamma);
		v.b=pow((is.get()/255.0),gamma);
		if(!is){
			throw error;
		}
	}
	is.get();
	if(is){
		throw error;
	}
	return b;
}