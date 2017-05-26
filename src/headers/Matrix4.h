#ifndef MATRIX4_H
#define MATRIX4_H
#include <cstddef>
#include <cmath>
#include <stdexcept>
#include <ostream>
#include <utility>
#include "Vector3.h"
#include "Quaternion.h"

struct Matrix4{
	private:
	double x[4][4];
	public:
	Matrix4(double x00,double x01,double x02,double x03,double x10,double x11,double x12,double x13,double x20,double x21,double x22,double x23,double x30,double x31,double x32,double x33)noexcept{
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
	inline Matrix4 operator*(double f)const noexcept{
		return Matrix4(x[0][0]*f,x[0][1]*f,x[0][2]*f,x[0][3]*f,x[1][0]*f,x[1][1]*f,x[1][2]*f,x[1][3]*f,x[2][0]*f,x[2][1]*f,x[2][2]*f,x[2][3]*f,x[3][0]*f,x[3][1]*f,x[3][2]*f,x[3][3]*f);
	}
	inline Matrix4 operator*(Matrix4 m)const noexcept{
		return Matrix4(x[0][0]*m.x[0][0]+x[0][1]*m.x[1][0]+x[0][2]*m.x[2][0]+x[0][3]*m.x[3][0],x[0][0]*m.x[0][1]+x[0][1]*m.x[1][1]+x[0][2]*m.x[2][1]+x[0][3]*m.x[3][1],x[0][0]*m.x[0][2]+x[0][1]*m.x[1][2]+x[0][2]*m.x[2][2]+x[0][3]*m.x[3][2],x[0][0]*m.x[0][3]+x[0][1]*m.x[1][3]+x[0][2]*m.x[2][3]+x[0][3]*m.x[3][3],x[1][0]*m.x[0][0]+x[1][1]*m.x[1][0]+x[1][2]*m.x[2][0]+x[1][3]*m.x[3][0],x[1][0]*m.x[0][1]+x[1][1]*m.x[1][1]+x[1][2]*m.x[2][1]+x[1][3]*m.x[3][1],x[1][0]*m.x[0][2]+x[1][1]*m.x[1][2]+x[1][2]*m.x[2][2]+x[1][3]*m.x[3][2],x[1][0]*m.x[0][3]+x[1][1]*m.x[1][3]+x[1][2]*m.x[2][3]+x[1][3]*m.x[3][3],x[2][0]*m.x[0][0]+x[2][1]*m.x[1][0]+x[2][2]*m.x[2][0]+x[2][3]*m.x[3][0],x[2][0]*m.x[0][1]+x[2][1]*m.x[1][1]+x[2][2]*m.x[2][1]+x[2][3]*m.x[3][1],x[2][0]*m.x[0][2]+x[2][1]*m.x[1][2]+x[2][2]*m.x[2][2]+x[2][3]*m.x[3][2],x[2][0]*m.x[0][3]+x[2][1]*m.x[1][3]+x[2][2]*m.x[2][3]+x[2][3]*m.x[3][3],x[3][0]*m.x[0][0]+x[3][1]*m.x[1][0]+x[3][2]*m.x[2][0]+x[3][3]*m.x[3][0],x[3][0]*m.x[0][1]+x[3][1]*m.x[1][1]+x[3][2]*m.x[2][1]+x[3][3]*m.x[3][1],x[3][0]*m.x[0][2]+x[3][1]*m.x[1][2]+x[3][2]*m.x[2][2]+x[3][3]*m.x[3][2],x[3][0]*m.x[0][3]+x[3][1]*m.x[1][3]+x[3][2]*m.x[2][3]+x[3][3]*m.x[3][3]);
	}
	inline Matrix4 operator/(double f)const noexcept{
		return Matrix4(x[0][0]/f,x[0][1]/f,x[0][2]/f,x[0][3]/f,x[1][0]/f,x[1][1]/f,x[1][2]/f,x[1][3]/f,x[2][0]/f,x[2][1]/f,x[2][2]/f,x[2][3]/f,x[3][0]/f,x[3][1]/f,x[3][2]/f,x[3][3]/f);
	}
	friend inline Matrix4 operator*(double f,Matrix4 m)noexcept{
		return m*f;
	}
	inline Matrix4& operator+=(Matrix4 m)noexcept{
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
		return *this;
	}
	inline Matrix4& operator-=(Matrix4 m)noexcept{
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
		return *this;
	}
	inline Matrix4& operator*=(double f)noexcept{
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
		return *this;
	}
	inline Matrix4& operator*=(Matrix4 m)noexcept{
		x[0][0]=x[0][0]*m.x[0][0]+x[0][1]*m.x[1][0]+x[0][2]*m.x[2][0]+x[0][3]*m.x[3][0];
		x[0][1]=x[0][0]*m.x[0][1]+x[0][1]*m.x[1][1]+x[0][2]*m.x[2][1]+x[0][3]*m.x[3][1];
		x[0][2]=x[0][0]*m.x[0][2]+x[0][1]*m.x[1][2]+x[0][2]*m.x[2][2]+x[0][3]*m.x[3][2];
		x[0][3]=x[0][0]*m.x[0][3]+x[0][1]*m.x[1][3]+x[0][2]*m.x[2][3]+x[0][3]*m.x[3][3];
		x[1][0]=x[1][0]*m.x[0][0]+x[1][1]*m.x[1][0]+x[1][2]*m.x[2][0]+x[1][3]*m.x[3][0];
		x[1][1]=x[1][0]*m.x[0][1]+x[1][1]*m.x[1][1]+x[1][2]*m.x[2][1]+x[1][3]*m.x[3][1];
		x[1][2]=x[1][0]*m.x[0][2]+x[1][1]*m.x[1][2]+x[1][2]*m.x[2][2]+x[1][3]*m.x[3][2];
		x[1][3]=x[1][0]*m.x[0][3]+x[1][1]*m.x[1][3]+x[1][2]*m.x[2][3]+x[1][3]*m.x[3][3];
		x[2][0]=x[2][0]*m.x[0][0]+x[2][1]*m.x[1][0]+x[2][2]*m.x[2][0]+x[2][3]*m.x[3][0];
		x[2][1]=x[2][0]*m.x[0][1]+x[2][1]*m.x[1][1]+x[2][2]*m.x[2][1]+x[2][3]*m.x[3][1];
		x[2][2]=x[2][0]*m.x[0][2]+x[2][1]*m.x[1][2]+x[2][2]*m.x[2][2]+x[2][3]*m.x[3][2];
		x[2][3]=x[2][0]*m.x[0][3]+x[2][1]*m.x[1][3]+x[2][2]*m.x[2][3]+x[2][3]*m.x[3][3];
		x[3][0]=x[3][0]*m.x[0][0]+x[3][1]*m.x[1][0]+x[3][2]*m.x[2][0]+x[3][3]*m.x[3][0];
		x[3][1]=x[3][0]*m.x[0][1]+x[3][1]*m.x[1][1]+x[3][2]*m.x[2][1]+x[3][3]*m.x[3][1];
		x[3][2]=x[3][0]*m.x[0][2]+x[3][1]*m.x[1][2]+x[3][2]*m.x[2][2]+x[3][3]*m.x[3][2];
		x[3][3]=x[3][0]*m.x[0][3]+x[3][1]*m.x[1][3]+x[3][2]*m.x[2][3]+x[3][3]*m.x[3][3];
		return *this;
	}
	inline Matrix4& operator/=(double f)noexcept{
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
		return *this;
	}
	inline bool operator==(Matrix4 m)const noexcept{
		return (x[0][0]==m.x[0][0])&&(x[0][1]==m.x[0][1])&&(x[0][2]==m.x[0][2])&&(x[0][3]==m.x[0][3])&&(x[1][0]==m.x[1][0])&&(x[1][1]==m.x[1][1])&&(x[1][2]==m.x[1][2])&&(x[1][3]==m.x[1][3])&&(x[2][0]==m.x[2][0])&&(x[2][1]==m.x[2][1])&&(x[2][2]==m.x[2][2])&&(x[2][3]==m.x[2][3])&&(x[3][0]==m.x[3][0])&&(x[3][1]==m.x[3][1])&&(x[3][2]==m.x[3][2])&&(x[3][3]==m.x[3][3]);
	}
	inline bool operator!=(Matrix4 m)const noexcept{
		return !(*this==m);
	}
	inline double& at(ptrdiff_t i,ptrdiff_t j){
		if(i<0||i>3||j<0||j>3){
			throw ::std::out_of_range("Matrix4 only have 4x4 fields.");
		}
		return x[i][j];
	}
	inline const double& at(ptrdiff_t i,ptrdiff_t j)const{
		if(i<0||i>3||j<0||j>3){
			throw ::std::out_of_range("Matrix4 only have 4x4 fields.");
		}
		return x[i][j];
	}
	inline Matrix4 transposed()const noexcept{
		return Matrix4(x[0][0],x[1][0],x[2][0],x[3][0],x[0][1],x[1][1],x[2][1],x[3][1],x[0][2],x[1][2],x[2][2],x[3][2],x[0][3],x[1][3],x[2][3],x[3][3]);
	}
	inline Matrix4& transpose()noexcept{
		::std::swap(x[0][1],x[1][0]);
		::std::swap(x[0][2],x[2][0]);
		::std::swap(x[0][3],x[3][0]);
		::std::swap(x[1][2],x[2][1]);
		::std::swap(x[1][3],x[3][1]);
		::std::swap(x[2][3],x[3][2]);
		return *this;
	}
	inline double determinant()const noexcept{
		return x[0][3]*x[1][2]*x[2][1]*x[3][0]-x[0][2]*x[1][3]*x[2][1]*x[3][0]-x[0][3]*x[1][1]*x[2][2]*x[3][0]+x[0][1]*x[1][3]*x[2][2]*x[3][0]+x[0][2]*x[1][1]*x[2][3]*x[3][0]-x[0][1]*x[1][2]*x[2][3]*x[3][0]-x[0][3]*x[1][2]*x[2][0]*x[3][1]+x[0][2]*x[1][3]*x[2][0]*x[3][1]+x[0][3]*x[1][0]*x[2][2]*x[3][1]-x[0][0]*x[1][3]*x[2][2]*x[3][1]-x[0][2]*x[1][0]*x[2][3]*x[3][1]+x[0][0]*x[1][2]*x[2][3]*x[3][1]+x[0][3]*x[1][1]*x[2][0]*x[3][2]-x[0][1]*x[1][3]*x[2][0]*x[3][2]-x[0][3]*x[1][0]*x[2][1]*x[3][2]+x[0][0]*x[1][3]*x[2][1]*x[3][2]+x[0][1]*x[1][0]*x[2][3]*x[3][2]-x[0][0]*x[1][1]*x[2][3]*x[3][2]-x[0][2]*x[1][1]*x[2][0]*x[3][3]+x[0][1]*x[1][2]*x[2][0]*x[3][3]+x[0][2]*x[1][0]*x[2][1]*x[3][3]-x[0][0]*x[1][2]*x[2][1]*x[3][3]-x[0][1]*x[1][0]*x[2][2]*x[3][3]+x[0][0]*x[1][1]*x[2][2]*x[3][3];
	}
	inline Matrix4 inversed()const noexcept{
		double det=this->determinant();
		if(det==0){
			return Matrix4();
		}
		return Matrix4((x[1][2]*x[2][3]*x[3][1]-x[1][3]*x[2][2]*x[3][1]+x[1][3]*x[2][1]*x[3][2]-x[1][1]*x[2][3]*x[3][2]-x[1][2]*x[2][1]*x[3][3]+x[1][1]*x[2][2]*x[3][3])/det,(x[0][3]*x[2][2]*x[3][1]-x[0][2]*x[2][3]*x[3][1]-x[0][3]*x[2][1]*x[3][2]+x[0][1]*x[2][3]*x[3][2]+x[0][2]*x[2][1]*x[3][3]-x[0][1]*x[2][2]*x[3][3])/det,(x[0][2]*x[1][3]*x[3][1]-x[0][3]*x[1][2]*x[3][1]+x[0][3]*x[1][1]*x[3][2]-x[0][1]*x[1][3]*x[3][2]-x[0][2]*x[1][1]*x[3][3]+x[0][1]*x[1][2]*x[3][3])/det,(x[0][3]*x[1][2]*x[2][1]-x[0][2]*x[1][3]*x[2][1]-x[0][3]*x[1][1]*x[2][2]+x[0][1]*x[1][3]*x[2][2]+x[0][2]*x[1][1]*x[2][3]-x[0][1]*x[1][2]*x[2][3])/det,(x[1][3]*x[2][2]*x[3][0]-x[1][2]*x[2][3]*x[3][0]-x[1][3]*x[2][0]*x[3][2]+x[1][0]*x[2][3]*x[3][2]+x[1][2]*x[2][0]*x[3][3]-x[1][0]*x[2][2]*x[3][3])/det,(x[0][2]*x[2][3]*x[3][0]-x[0][3]*x[2][2]*x[3][0]+x[0][3]*x[2][0]*x[3][2]-x[0][0]*x[2][3]*x[3][2]-x[0][2]*x[2][0]*x[3][3]+x[0][0]*x[2][2]*x[3][3])/det,(x[0][3]*x[1][2]*x[3][0]-x[0][2]*x[1][3]*x[3][0]-x[0][3]*x[1][0]*x[3][2]+x[0][0]*x[1][3]*x[3][2]+x[0][2]*x[1][0]*x[3][3]-x[0][0]*x[1][2]*x[3][3])/det,(x[0][2]*x[1][3]*x[2][0]-x[0][3]*x[1][2]*x[2][0]+x[0][3]*x[1][0]*x[2][2]-x[0][0]*x[1][3]*x[2][2]-x[0][2]*x[1][0]*x[2][3]+x[0][0]*x[1][2]*x[2][3])/det,(x[1][1]*x[2][3]*x[3][0]-x[1][3]*x[2][1]*x[3][0]+x[1][3]*x[2][0]*x[3][1]-x[1][0]*x[2][3]*x[3][1]-x[1][1]*x[2][0]*x[3][3]+x[1][0]*x[2][1]*x[3][3])/det,(x[0][3]*x[2][1]*x[3][0]-x[0][1]*x[2][3]*x[3][0]-x[0][3]*x[2][0]*x[3][1]+x[0][0]*x[2][3]*x[3][1]+x[0][1]*x[2][0]*x[3][3]-x[0][0]*x[2][1]*x[3][3])/det,(x[0][1]*x[1][3]*x[3][0]-x[0][3]*x[1][1]*x[3][0]+x[0][3]*x[1][0]*x[3][1]-x[0][0]*x[1][3]*x[3][1]-x[0][1]*x[1][0]*x[3][3]+x[0][0]*x[1][1]*x[3][3])/det,(x[0][3]*x[1][1]*x[2][0]-x[0][1]*x[1][3]*x[2][0]-x[0][3]*x[1][0]*x[2][1]+x[0][0]*x[1][3]*x[2][1]+x[0][1]*x[1][0]*x[2][3]-x[0][0]*x[1][1]*x[2][3])/det,(x[1][2]*x[2][1]*x[3][0]-x[1][1]*x[2][2]*x[3][0]-x[1][2]*x[2][0]*x[3][1]+x[1][0]*x[2][2]*x[3][1]+x[1][1]*x[2][0]*x[3][2]-x[1][0]*x[2][1]*x[3][2])/det,(x[0][1]*x[2][2]*x[3][0]-x[0][2]*x[2][1]*x[3][0]+x[0][2]*x[2][0]*x[3][1]-x[0][0]*x[2][2]*x[3][1]-x[0][1]*x[2][0]*x[3][2]+x[0][0]*x[2][1]*x[3][2])/det,(x[0][2]*x[1][1]*x[3][0]-x[0][1]*x[1][2]*x[3][0]-x[0][2]*x[1][0]*x[3][1]+x[0][0]*x[1][2]*x[3][1]+x[0][1]*x[1][0]*x[3][2]-x[0][0]*x[1][1]*x[3][2])/det,(x[0][1]*x[1][2]*x[2][0]-x[0][2]*x[1][1]*x[2][0]+x[0][2]*x[1][0]*x[2][1]-x[0][0]*x[1][2]*x[2][1]-x[0][1]*x[1][0]*x[2][2]+x[0][0]*x[1][1]*x[2][2])/det);
	}
	inline Matrix4& inverse()noexcept{
		double det=this->determinant();
		if(det==0){
			x[0][0]=1;
			x[0][1]=0;
			x[0][2]=0;
			x[0][3]=0;
			x[1][0]=0;
			x[1][1]=1;
			x[1][2]=0;
			x[1][3]=0;
			x[2][0]=0;
			x[2][1]=0;
			x[2][2]=1;
			x[2][3]=0;
			x[3][0]=0;
			x[3][1]=0;
			x[3][2]=0;
			x[3][3]=1;
			return *this;
		}
		double x00=x[1][2]*x[2][3]*x[3][1]-x[1][3]*x[2][2]*x[3][1]+x[1][3]*x[2][1]*x[3][2]-x[1][1]*x[2][3]*x[3][2]-x[1][2]*x[2][1]*x[3][3]+x[1][1]*x[2][2]*x[3][3];
		double x01=x[0][3]*x[2][2]*x[3][1]-x[0][2]*x[2][3]*x[3][1]-x[0][3]*x[2][1]*x[3][2]+x[0][1]*x[2][3]*x[3][2]+x[0][2]*x[2][1]*x[3][3]-x[0][1]*x[2][2]*x[3][3];
		double x02=x[0][2]*x[1][3]*x[3][1]-x[0][3]*x[1][2]*x[3][1]+x[0][3]*x[1][1]*x[3][2]-x[0][1]*x[1][3]*x[3][2]-x[0][2]*x[1][1]*x[3][3]+x[0][1]*x[1][2]*x[3][3];
		double x03=x[0][3]*x[1][2]*x[2][1]-x[0][2]*x[1][3]*x[2][1]-x[0][3]*x[1][1]*x[2][2]+x[0][1]*x[1][3]*x[2][2]+x[0][2]*x[1][1]*x[2][3]-x[0][1]*x[1][2]*x[2][3];
		double x10=x[1][3]*x[2][2]*x[3][0]-x[1][2]*x[2][3]*x[3][0]-x[1][3]*x[2][0]*x[3][2]+x[1][0]*x[2][3]*x[3][2]+x[1][2]*x[2][0]*x[3][3]-x[1][0]*x[2][2]*x[3][3];
		double x11=x[0][2]*x[2][3]*x[3][0]-x[0][3]*x[2][2]*x[3][0]+x[0][3]*x[2][0]*x[3][2]-x[0][0]*x[2][3]*x[3][2]-x[0][2]*x[2][0]*x[3][3]+x[0][0]*x[2][2]*x[3][3];
		double x12=x[0][3]*x[1][2]*x[3][0]-x[0][2]*x[1][3]*x[3][0]-x[0][3]*x[1][0]*x[3][2]+x[0][0]*x[1][3]*x[3][2]+x[0][2]*x[1][0]*x[3][3]-x[0][0]*x[1][2]*x[3][3];
		double x13=x[0][2]*x[1][3]*x[2][0]-x[0][3]*x[1][2]*x[2][0]+x[0][3]*x[1][0]*x[2][2]-x[0][0]*x[1][3]*x[2][2]-x[0][2]*x[1][0]*x[2][3]+x[0][0]*x[1][2]*x[2][3];
		double x20=x[1][1]*x[2][3]*x[3][0]-x[1][3]*x[2][1]*x[3][0]+x[1][3]*x[2][0]*x[3][1]-x[1][0]*x[2][3]*x[3][1]-x[1][1]*x[2][0]*x[3][3]+x[1][0]*x[2][1]*x[3][3];
		double x21=x[0][3]*x[2][1]*x[3][0]-x[0][1]*x[2][3]*x[3][0]-x[0][3]*x[2][0]*x[3][1]+x[0][0]*x[2][3]*x[3][1]+x[0][1]*x[2][0]*x[3][3]-x[0][0]*x[2][1]*x[3][3];
		double x22=x[0][1]*x[1][3]*x[3][0]-x[0][3]*x[1][1]*x[3][0]+x[0][3]*x[1][0]*x[3][1]-x[0][0]*x[1][3]*x[3][1]-x[0][1]*x[1][0]*x[3][3]+x[0][0]*x[1][1]*x[3][3];
		double x23=x[0][3]*x[1][1]*x[2][0]-x[0][1]*x[1][3]*x[2][0]-x[0][3]*x[1][0]*x[2][1]+x[0][0]*x[1][3]*x[2][1]+x[0][1]*x[1][0]*x[2][3]-x[0][0]*x[1][1]*x[2][3];
		double x30=x[1][2]*x[2][1]*x[3][0]-x[1][1]*x[2][2]*x[3][0]-x[1][2]*x[2][0]*x[3][1]+x[1][0]*x[2][2]*x[3][1]+x[1][1]*x[2][0]*x[3][2]-x[1][0]*x[2][1]*x[3][2];
		double x31=x[0][1]*x[2][2]*x[3][0]-x[0][2]*x[2][1]*x[3][0]+x[0][2]*x[2][0]*x[3][1]-x[0][0]*x[2][2]*x[3][1]-x[0][1]*x[2][0]*x[3][2]+x[0][0]*x[2][1]*x[3][2];
		double x32=x[0][2]*x[1][1]*x[3][0]-x[0][1]*x[1][2]*x[3][0]-x[0][2]*x[1][0]*x[3][1]+x[0][0]*x[1][2]*x[3][1]+x[0][1]*x[1][0]*x[3][2]-x[0][0]*x[1][1]*x[3][2];
		double x33=x[0][1]*x[1][2]*x[2][0]-x[0][2]*x[1][1]*x[2][0]+x[0][2]*x[1][0]*x[2][1]-x[0][0]*x[1][2]*x[2][1]-x[0][1]*x[1][0]*x[2][2]+x[0][0]*x[1][1]*x[2][2];
		x[0][0]=x00/det;
		x[0][1]=x01/det;
		x[0][2]=x02/det;
		x[0][3]=x03/det;
		x[1][0]=x10/det;
		x[1][1]=x11/det;
		x[1][2]=x12/det;
		x[1][3]=x13/det;
		x[2][0]=x20/det;
		x[2][1]=x21/det;
		x[2][2]=x22/det;
		x[2][3]=x23/det;
		x[3][0]=x30/det;
		x[3][1]=x31/det;
		x[3][2]=x32/det;
		x[3][3]=x33/det;
		return *this;
	}
	friend inline Vector3 apply(Matrix4 m,Vector3 v)noexcept{
		double w=m.x[3][0]*v.x+m.x[3][1]*v.y+m.x[3][2]*v.z+m.x[3][3];
		return Vector3((m.x[0][0]*v.x+m.x[0][1]*v.y+m.x[0][2]*v.z+m.x[0][3])/w,(m.x[1][0]*v.x+m.x[1][1]*v.y+m.x[1][2]*v.z+m.x[1][3])/w,(m.x[2][0]*v.x+m.x[2][1]*v.y+m.x[2][2]*v.z+m.x[2][3])/w);
	}
	friend inline Vector3& applyTo(Matrix4 m,Vector3& v)noexcept{
		double w=m.x[3][0]*v.x+m.x[3][1]*v.y+m.x[3][2]*v.z+m.x[3][3];
		v.x=(m.x[0][0]*v.x+m.x[0][1]*v.y+m.x[0][2]*v.z+m.x[0][3])/w;
		v.y=(m.x[1][0]*v.x+m.x[1][1]*v.y+m.x[1][2]*v.z+m.x[1][3])/w;
		v.z=(m.x[2][0]*v.x+m.x[2][1]*v.y+m.x[2][2]*v.z+m.x[2][3])/w;
		return v;
	}
	friend inline void applyTo(Matrix4 m,double& a,double& b,double& c,double& d){
		double x=m.x[0][0]*a+m.x[0][1]*b+m.x[0][2]*c+m.x[0][3]*d;
		double y=m.x[1][0]*a+m.x[1][1]*b+m.x[1][2]*c+m.x[1][3]*d;
		double z=m.x[2][0]*a+m.x[2][1]*b+m.x[2][2]*c+m.x[2][3]*d;
		double w=m.x[3][0]*a+m.x[3][1]*b+m.x[3][2]*c+m.x[3][3]*d;
		a=x;
		b=y;
		c=z;
		d=w;
	}
	friend inline ::std::ostream& operator<<(::std::ostream& os,const Matrix4& m)noexcept{
		os<<"[["<<m.x[0][0]<<" "<<m.x[0][1]<<" "<<m.x[0][2]<<" "<<m.x[0][3]<<"] "<<"\n";
		os<<" ["<<m.x[1][0]<<" "<<m.x[1][1]<<" "<<m.x[1][2]<<" "<<m.x[1][3]<<"] "<<"\n";
		os<<" ["<<m.x[2][0]<<" "<<m.x[2][1]<<" "<<m.x[2][2]<<" "<<m.x[2][3]<<"] "<<"\n";
		os<<" ["<<m.x[3][0]<<" "<<m.x[3][1]<<" "<<m.x[3][2]<<" "<<m.x[3][3]<<"]]"<<"\n";
		return os;
	}
	static inline Matrix4 fromTranslation(Vector3 trans){
		return Matrix4(1,0,0,trans.x,0,1,0,trans.y,0,0,1,trans.z,0,0,0,1);
	}
	static inline Matrix4 fromQuaternion(Quaternion q){
		return Matrix4(1-2*(q.y*q.y+q.z*q.z),2*(q.x*q.y-q.z*q.w),2*(q.x*q.z+q.y*q.w),0,2*(q.x*q.y+q.z*q.w),1-2*(q.x*q.x+q.z*q.z),2*(q.y*q.z-q.x*q.w),0,2*(q.x*q.z-q.y*q.w),2*(q.y*q.z+q.x*q.w),1-2*(q.x*q.x+q.y*q.y),0,0,0,0,1);
	}
};

#endif //MATRIX4_H