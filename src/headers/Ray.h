#ifndef RAY_H
#define RAY_H
class Ray{
	Vector3 direction;
	public:
	Vector3 start;
	Ray(Vector3 direction=Vector3(1,0,0),Vector3 start=Vector3(0,0,0))noexcept:direction(direction.normalized()),start(start){}
	inline Vector3 getDirection()const noexcept{
		return this->direction;
	}
	inline void setDirection(Vector3 direction)noexcept{
		this->direction=direction.normalized();
	}
	friend inline ::std::ostream& operator<<(::std::ostream& os,const Ray& r)noexcept{
		os<<"(Ray "<<r.start<<" -> "<<r.direction<<" )";
		return os;
	}
	inline void step(float distance)noexcept{
		this->start+=distance*this->direction;
	}
};
#endif //RAY_H