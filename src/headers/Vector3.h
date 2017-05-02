#ifndef VECTOR3_H
#define VECTOR3_H
#include <cstddef>
#include <cmath>
#include <stdexcept>
#include <ostream>

struct Vector3{
	union{double x;double r;};
	union{double y;double g;};
	union{double z;double b;};
	Vector3(double x,double y,double z)noexcept:x(x),y(y),z(z){}
	Vector3()noexcept:Vector3(0,0,0){}
	inline Vector3 operator+(Vector3 v)const noexcept{
		return Vector3(this->x+v.x,this->y+v.y,this->z+v.z);
	}
	inline Vector3 operator-(Vector3 v)const noexcept{
		return Vector3(this->x-v.x,this->y-v.y,this->z-v.z);
	}
	inline Vector3 operator*(double f)const noexcept{
		return Vector3(this->x*f,this->y*f,this->z*f);
	}
	inline Vector3 operator/(double f)const noexcept{
		return Vector3(this->x/f,this->y/f,this->z/f);
	}
	friend inline Vector3 operator*(double f,Vector3 v)noexcept{
		return v*f;
	}
	inline Vector3& operator+=(Vector3 v)noexcept{
		this->x+=v.x;
		this->y+=v.y;
		this->z+=v.z;
		return *this;
	}
	inline Vector3& operator-=(Vector3 v)noexcept{
		this->x-=v.x;
		this->y-=v.y;
		this->z-=v.z;
		return *this;
	}
	inline Vector3& operator*=(double f)noexcept{
		this->x*=f;
		this->y*=f;
		this->z*=f;
		return *this;
	}
	inline Vector3& operator/=(double f)noexcept{
		this->x/=f;
		this->y/=f;
		this->z/=f;
		return *this;
	}
	inline bool operator==(Vector3 v)const noexcept{
		return (this->x==v.x)&&(this->y==v.y)&&(this->z==v.z);
	}
	inline bool operator!=(Vector3 v)const noexcept{
		return !(*this==v);
	}
	inline double& operator[](ptrdiff_t i){
		if(i<0||i>2){
			throw ::std::out_of_range("Vector3 only have 3 fields.");
		}
		return i==0?(this->x):i==1?(this->y):(this->z);
	}
	inline const double& operator[](ptrdiff_t i)const{
		if(i<0||i>2){
			throw ::std::out_of_range("Vector3 only have 3 fields.");
		}
		return i==0?(this->x):i==1?(this->y):(this->z);
	}
	friend inline double dot(Vector3 v,Vector3 u)noexcept{
		return u.x*v.x+u.y*v.y+u.z*v.z;
	}
	friend inline Vector3 cross(Vector3 v,Vector3 u)noexcept{
		return Vector3(v.y*u.z-v.z*u.y,v.z*u.x-v.x*u.z,v.x*u.y-v.y*u.x);
	}
	inline Vector3 scaled(Vector3 s)noexcept{
		return Vector3(this->x*s.x,this->y*s.y,this->z*s.z);
	}
	inline Vector3& scale(Vector3 s)noexcept{
		this->x*=s.x;
		this->y*=s.y;
		this->z*=s.z;
		return *this;
	}
	inline double length()const noexcept{
		return ::std::sqrt(this->sqrLength());
	}
	inline double sqrLength()const noexcept{
		return dot(*this,*this);
	}
	inline Vector3 normalized()const noexcept{
		return *this/this->length();
	}
	inline Vector3& normalize()noexcept{
		*this/=this->length();
		return *this;
	}
	friend inline ::std::ostream& operator<<(::std::ostream& os,const Vector3& v)noexcept{
		os<<"("<<v.x<<","<<v.y<<","<<v.z<<")";
		return os;
	}
};

#endif //VECTOR3_H