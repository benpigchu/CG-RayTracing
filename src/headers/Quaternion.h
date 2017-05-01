#ifndef QUATERNION_H
#define QUATERNION_H
#include <cmath>
#include <ostream>
#include "Vector3.h"

// xi+yj+zk+w
struct Quaternion{
	double x,y,z,w;
	Quaternion(double x,double y,double z,double w)noexcept:x(x),y(y),z(z),w(w){}
	Quaternion()noexcept:Quaternion(0,0,0,1){}
	inline Quaternion operator+(Quaternion q)const noexcept{
		return Quaternion(this->x+q.x,this->y+q.y,this->z+q.z,this->w+q.w);
	}
	inline Quaternion operator-(Quaternion q)const noexcept{
		return Quaternion(this->x-q.x,this->y-q.y,this->z-q.z,this->w-q.w);
	}
	inline Quaternion operator*(double f)const noexcept{
		return Quaternion(this->x*f,this->y*f,this->z*f,this->w*f);
	}
	inline Quaternion operator*(Quaternion q)const noexcept{
		return Quaternion(this->x*q.w+this->w*q.x+this->y*q.z-this->z*q.y,this->y*q.w+this->w*q.y+this->z*q.x-this->x*q.z,this->z*q.w+this->w*q.z+this->x*q.y-this->y*q.x,this->w*q.w-this->x*q.x-this->y*q.y-this->z*q.z);
	}
	inline Quaternion operator/(double f)const noexcept{
		return Quaternion(this->x/f,this->y/f,this->z/f,this->w/f);
	}
	friend inline Quaternion operator*(double f,Quaternion q)noexcept{
		return q*f;
	}
	inline Quaternion& operator+=(Quaternion q)noexcept{
		this->x+=q.x;
		this->y+=q.y;
		this->z+=q.z;
		this->w+=q.w;
		return *this;
	}
	inline Quaternion& operator-=(Quaternion q)noexcept{
		this->x-=q.x;
		this->y-=q.y;
		this->z-=q.z;
		this->w-=q.w;
		return *this;
	}
	inline Quaternion& operator*=(double f)noexcept{
		this->x*=f;
		this->y*=f;
		this->z*=f;
		this->w*=f;
		return *this;
	}
	inline Quaternion& operator*=(Quaternion q)noexcept{
		double xx=this->x*q.w+this->w*q.x+this->y*q.z-this->z*q.y;
		double yy=this->y*q.w+this->w*q.y+this->z*q.x-this->x*q.z;
		double zz=this->z*q.w+this->w*q.z+this->x*q.y-this->y*q.x;
		double ww=this->w*q.w-this->x*q.x-this->y*q.y-this->z*q.z;
		this->x=xx;
		this->y=yy;
		this->z=zz;
		this->w=ww;
		return *this;
	}
	inline Quaternion& operator/=(double f)noexcept{
		this->x/=f;
		this->y/=f;
		this->z/=f;
		this->w/=f;
		return *this;
	}
	inline bool operator==(Quaternion q)const noexcept{
		return (this->x==q.x)&&(this->y==q.y)&&(this->z==q.z)&&(this->w==q.w);
	}
	inline bool operator!=(Quaternion q)const noexcept{
		return !(*this==q);
	}
	inline Quaternion conjugated()const noexcept{
		return Quaternion(-x,-y,-z,w);
	}
	inline Quaternion& conjugate()noexcept{
		this->x*=-1;
		this->y*=-1;
		this->z*=-1;
		return *this;
	}
	inline double sqrLength()const noexcept{
		return this->x*this->x+this->y*this->y+this->z*this->z+this->w*this->w;
	}
	inline double length()const noexcept{
		return ::std::sqrt(this->sqrLength());
	}
	inline Quaternion normalized()const noexcept{
		double l=this->length();
		return Quaternion(x/l,y/l,z/l,w/l);
	}
	inline Quaternion& normalize()noexcept{
		double l=this->length();
		this->x/=l;
		this->y/=l;
		this->z/=l;
		this->w/=l;
		return *this;
	}
	inline Quaternion inversed()const noexcept{
		double l=this->sqrLength();
		return Quaternion(-x/l,-y/l,-z/l,w/l);
	}
	inline Quaternion& inverse()noexcept{
		double l=this->sqrLength();
		this->x/=-l;
		this->y/=-l;
		this->z/=-l;
		this->w/=l;
		return *this;
	}
	friend inline Vector3 apply(Quaternion q,Vector3 v)noexcept{
		Quaternion vq(v.x,v.y,v.z,0);
		Quaternion result=q*vq*q.conjugated();
		return Vector3(result.x,result.y,result.z);
	}
	friend inline Vector3& applyTo(Quaternion q,Vector3& v)noexcept{
		Quaternion vq(v.x,v.y,v.z,0);
		Quaternion result=q*vq*q.conjugated();
		v.x=result.x;
		v.y=result.y;
		v.z=result.z;
		return v;
	}
	friend inline ::std::ostream& operator<<(::std::ostream& os,const Quaternion& q)noexcept{
		os<<"("<<q.x<<"i+ "<<q.y<<"j+ "<<q.z<<"k+ "<<q.w<<")";
		return os;
	}
	static inline Quaternion fromAxisRotation(Vector3 axis,double angle)noexcept{
		Vector3 ax=axis.normalized();
		double ha=angle/2;
		double s=sin(ha);
		return Quaternion(ax.x*s,ax.y*s,ax.z*s,cos(ha));
	}
};

#endif //QUATERNION_H