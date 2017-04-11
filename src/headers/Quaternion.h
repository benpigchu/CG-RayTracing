#ifndef QUATERNION_H
#define QUATERNION_H
#include <cmath>
#include <ostream>
#include "Vector3.h"

// xi+yj+zk+w
struct Quaternion{
	float x,y,z,w;
	Quaternion(float x,float y,float z,float w)noexcept:x(x),y(y),z(z),w(w){}
	Quaternion()noexcept:Quaternion(0,0,0,1){}
	inline Quaternion operator*(Quaternion q)const noexcept{
		return Quaternion(this->x*q.w+this->w*q.x+this->y*q.z-this->z*q.y,this->y*q.w+this->w*q.y+this->z*q.x-this->x*q.z,this->z*q.w+this->w*q.z+this->x*q.y-this->y*q.x,this->w*q.w-this->x*q.x-this->y*q.y-this->z*q.z);
	}
	inline Quaternion& operator*=(Quaternion q)noexcept{
		float xx=this->x*q.w+this->w*q.x+this->y*q.z-this->z*q.y;
		float yy=this->y*q.w+this->w*q.y+this->z*q.x-this->x*q.z;
		float zz=this->z*q.w+this->w*q.z+this->x*q.y-this->y*q.x;
		float ww=this->w*q.w-this->x*q.x-this->y*q.y-this->z*q.z;
		this->x=xx;
		this->y=yy;
		this->z=zz;
		this->w=ww;
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
	inline float sqrLength()const noexcept{
		return this->x*this->x+this->y*this->y+this->z*this->z+this->w*this->w;
	}
	inline float length()const noexcept{
		return ::std::sqrt(this->sqrLength());
	}
	inline Quaternion normalized()const noexcept{
		float l=this->length();
		return Quaternion(x/l,y/l,z/l,w/l);
	}
	inline Quaternion& normalize()noexcept{
		float l=this->length();
		this->x/=l;
		this->y/=l;
		this->z/=l;
		this->w/=l;
		return *this;
	}
	inline Quaternion inversed()const noexcept{
		float l=this->sqrLength();
		return Quaternion(-x/l,-y/l,-z/l,w/l);
	}
	inline Quaternion& inverse()noexcept{
		float l=this->sqrLength();
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
	static inline Quaternion fromAxisRotation(Vector3 axis,float angle)noexcept{
		Vector3 ax=axis.normalized();
		float ha=angle/2;
		float s=sin(ha);
		return Quaternion(ax.x*s,ax.y*s,ax.z*s,cos(ha));
	}
};

#endif //QUATERNION_H