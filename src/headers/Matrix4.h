#ifndef MATRIX4_H
#define MATRIX4_H
#include <cstddef>
#include <cmath>
#include <stdexcept>
#include <ostream>
//x00,x01,x02,x03,x10,x11,x12,x13,x20,x21,x22,x23,x30,x31,x32,x33,
struct Matrix4{
	private:
	float x[4][4];
	public:
	Matrix4(float x00,float x01,float x02,float x03,float x10,float x11,float x12,float x13,float x20,float x21,float x22,float x23,float x30,float x31,float x32,float x33)noexcept{
		x[0][0]=x00;
		x[0][1]=x01;
		x[0][2]=x02;
		x[0][3]=x03;
		x[1][0]=x10;
		x[1][1]=x11;
		x[1][2]=x12;
		x[1][3]=x13;
		x[2][0]=x20;
		x[2][1]=x21;
		x[2][2]=x22;
		x[2][3]=x23;
		x[3][0]=x30;
		x[3][1]=x31;
		x[3][2]=x32;
		x[3][3]=x33;
	}
	Matrix4()noexcept:Matrix4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1){}
	inline Matrix4 operator+(Matrix4 m)const noexcept{
		return Matrix4(x[0][0]+m.x[0][0],x[0][1]+m.x[0][1],x[0][2]+m.x[0][2],x[0][3]+m.x[0][3],x[1][0]+m.x[1][0],x[1][1]+m.x[1][1],x[1][2]+m.x[1][2],x[1][3]+m.x[1][3],x[2][0]+m.x[2][0],x[2][1]+m.x[2][1],x[2][2]+m.x[2][2],x[2][3]+m.x[2][3],x[3][0]+m.x[3][0],x[3][1]+m.x[3][1],x[3][2]+m.x[3][2],x[3][3]+m.x[3][3]);
	}
	inline Matrix4 operator-(Matrix4 m)const noexcept{
		return Matrix4(x[0][0]-m.x[0][0],x[0][1]-m.x[0][1],x[0][2]-m.x[0][2],x[0][3]-m.x[0][3],x[1][0]-m.x[1][0],x[1][1]-m.x[1][1],x[1][2]-m.x[1][2],x[1][3]-m.x[1][3],x[2][0]-m.x[2][0],x[2][1]-m.x[2][1],x[2][2]-m.x[2][2],x[2][3]-m.x[2][3],x[3][0]-m.x[3][0],x[3][1]-m.x[3][1],x[3][2]-m.x[3][2],x[3][3]-m.x[3][3]);
	}
	inline Matrix4 operator*(float f)const noexcept{
		return Matrix4(x[0][0]*f,x[0][1]*f,x[0][2]*f,x[0][3]*f,x[1][0]*f,x[1][1]*f,x[1][2]*f,x[1][3]*f,x[2][0]*f,x[2][1]*f,x[2][2]*f,x[2][3]*f,x[3][0]*f,x[3][1]*f,x[3][2]*f,x[3][3]*f);
	}
	inline Matrix4 operator/(float f)const noexcept{
		return Matrix4(x[0][0]/f,x[0][1]/f,x[0][2]/f,x[0][3]/f,x[1][0]/f,x[1][1]/f,x[1][2]/f,x[1][3]/f,x[2][0]/f,x[2][1]/f,x[2][2]/f,x[2][3]/f,x[3][0]/f,x[3][1]/f,x[3][2]/f,x[3][3]/f);
	}
	friend inline Matrix4 operator*(float f,Matrix4 m)noexcept{
		return m*f;
	}
	inline Matrix4 operator+=(Matrix4 m)noexcept{
		x[0][0]+=m.x[0][0];
		x[0][1]+=m.x[0][1];
		x[0][2]+=m.x[0][2];
		x[0][3]+=m.x[0][3];
		x[1][0]+=m.x[1][0];
		x[1][1]+=m.x[1][1];
		x[1][2]+=m.x[1][2];
		x[1][3]+=m.x[1][3];
		x[2][0]+=m.x[2][0];
		x[2][1]+=m.x[2][1];
		x[2][2]+=m.x[2][2];
		x[2][3]+=m.x[2][3];
		x[3][0]+=m.x[3][0];
		x[3][1]+=m.x[3][1];
		x[3][2]+=m.x[3][2];
		x[3][3]+=m.x[3][3];
	}
	inline Matrix4 operator-=(Matrix4 m)noexcept{
		x[0][0]-=m.x[0][0];
		x[0][1]-=m.x[0][1];
		x[0][2]-=m.x[0][2];
		x[0][3]-=m.x[0][3];
		x[1][0]-=m.x[1][0];
		x[1][1]-=m.x[1][1];
		x[1][2]-=m.x[1][2];
		x[1][3]-=m.x[1][3];
		x[2][0]-=m.x[2][0];
		x[2][1]-=m.x[2][1];
		x[2][2]-=m.x[2][2];
		x[2][3]-=m.x[2][3];
		x[3][0]-=m.x[3][0];
		x[3][1]-=m.x[3][1];
		x[3][2]-=m.x[3][2];
		x[3][3]-=m.x[3][3];
	}
	inline Matrix4 operator*=(float f)noexcept{
		x[0][0]*=f;
		x[0][1]*=f;
		x[0][2]*=f;
		x[0][3]*=f;
		x[1][0]*=f;
		x[1][1]*=f;
		x[1][2]*=f;
		x[1][3]*=f;
		x[2][0]*=f;
		x[2][1]*=f;
		x[2][2]*=f;
		x[2][3]*=f;
		x[3][0]*=f;
		x[3][1]*=f;
		x[3][2]*=f;
		x[3][3]*=f;
	}
	inline Matrix4 operator/=(float f)noexcept{
		x[0][0]/=f;
		x[0][1]/=f;
		x[0][2]/=f;
		x[0][3]/=f;
		x[1][0]/=f;
		x[1][1]/=f;
		x[1][2]/=f;
		x[1][3]/=f;
		x[2][0]/=f;
		x[2][1]/=f;
		x[2][2]/=f;
		x[2][3]/=f;
		x[3][0]/=f;
		x[3][1]/=f;
		x[3][2]/=f;
		x[3][3]/=f;
	}
	inline float& value(ptrdiff_t i,ptrdiff_t j){
		if(i<0||i>3||j<0||j>3){
			throw ::std::out_of_range("Matrix4 only have 4x4 fields.");
		}
		return x[i][j];
	}
	inline const float& value(ptrdiff_t i,ptrdiff_t j)const{
		if(i<0||i>3||j<0||j>3){
			throw ::std::out_of_range("Matrix4 only have 4x4 fields.");
		}
		return x[i][j];
	}
	friend inline ::std::ostream& operator<<(::std::ostream& os,const Matrix4& m)noexcept{
		os<<"[["<<m.x[0][0]<<" "<<m.x[0][1]<<" "<<m.x[0][2]<<" "<<m.x[0][3]<<"] "<<"\n";
		os<<" ["<<m.x[1][0]<<" "<<m.x[1][1]<<" "<<m.x[1][2]<<" "<<m.x[1][3]<<"] "<<"\n";
		os<<" ["<<m.x[2][0]<<" "<<m.x[2][1]<<" "<<m.x[2][2]<<" "<<m.x[2][3]<<"] "<<"\n";
		os<<" ["<<m.x[3][0]<<" "<<m.x[3][1]<<" "<<m.x[3][2]<<" "<<m.x[3][3]<<"]]"<<"\n";
		return os;
	}
};

#endif //MATRIX4_H