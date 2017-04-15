#include <ostream>
#include <cmath>
#include "Vector3.h"
#include "Bitmap.h"

void Bitmap::exportAsPPM(::std::ostream& os,float gamma)const noexcept{
	auto printFloat=[&os,gamma](float f){
		float gammaedF=pow(f,1.0f/gamma);
		if(gammaedF>1.0f){
			gammaedF=1.0f;
		}
		if(gammaedF<0.0f){
			gammaedF=0.0f;
		}
		os<<static_cast<unsigned char>(gammaedF*255.0f+0.5f);
	};
	os<<"P6 "<<this->width<<" "<<this->height<<" 255\n";
	for(const Vector3 v:this->data){
		printFloat(v.r);
		printFloat(v.g);
		printFloat(v.b);
	}
}