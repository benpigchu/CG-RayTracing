#ifndef CAMERA_H
#define CAMERA_H
#include <ostream>
#include "Transform.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Ray.h"
#include "Bitmap.h"
#include "Scene.h"

struct Camera{
	Transform transform;
	float zoom;
	Camera(float zoom,Vector3 position=Vector3(0,0,0),Quaternion rotation=Quaternion())noexcept:zoom(zoom),transform(position,rotation){}
	Camera(float zoom,Transform transform)noexcept:zoom(zoom),transform(transform){}
	inline Ray makeRay(float x,float y)noexcept{
		return Ray(apply(transform.getRotation(),Vector3(x,y,zoom)),transform.getPosition());
	}
	friend inline ::std::ostream& operator<<(::std::ostream& os,const Camera& c)noexcept{
		os<<"(Camera zoom:"<<c.zoom<<" transform:"<<c.transform<<")";
		return os;
	}
	void render(Bitmap& bitmap,const Scene& scene)noexcept;
};

#endif //CAMERA_H