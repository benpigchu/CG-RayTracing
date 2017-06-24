#ifndef BITMAP_H
#define BITMAP_H
#include <cstddef>
#include <vector>
#include <stdexcept>
#include <ostream>
#include <istream>
#include "Vector3.h"

class Bitmap{
	::std::vector<Vector3> data;
	size_t height,width;
	public:
	Bitmap(size_t width,size_t height)noexcept:height(height),width(width),data(::std::vector<Vector3>(height*width)){}
	inline const Vector3& at(ptrdiff_t x,ptrdiff_t y)const{
		if(x<0||x>=width||y<0||y>=height){
			throw ::std::out_of_range("Bitmap element access out of range.");
		}
		return this->data[x+y*this->width];
	}
	inline size_t getHeight()noexcept{
		return this->height;
	}
	inline size_t getWidth()noexcept{
		return this->width;
	}
	inline Vector3& at(ptrdiff_t x,ptrdiff_t y){
		if(x<0||x>=width||y<0||y>=height){
			throw ::std::out_of_range("Bitmap element access out of range.");
		}
		return this->data[x+y*this->width];
	}
	friend inline ::std::ostream& operator<<(::std::ostream& os,const Bitmap& m)noexcept{
		os<<"(Bitmap "<<m.width<<"x"<<m.height<<")";
		return os;
	}
	inline Vector3 sample(double u,double v)const{
		return this->at(ptrdiff_t(u*this->width),ptrdiff_t(v*this->height));
	}
	void exportAsPPM(::std::ostream& os,double gamma=1.0f)const noexcept;
	static Bitmap importFromPPM(::std::istream& is,double gamma=1.0f);
};


#endif //BITMAP_H