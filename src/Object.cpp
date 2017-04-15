#include "Object.h"
#include "Geometry.h"
#include "Vector3.h"
#include "Ray.h"
#include "Matrix4.h"
#include "Quaternion.h"

IntersectInfo Object::testIntersect(Ray r)const noexcept{
	IntersectInfo ii;
	if(!(this->geometry)){
		ii.isIntersect=false;
		return ii;
	}
	Ray rayBeforeTransform=Ray(apply(this->transform.getRotation().conjugated(),r.getDirection()),apply(this->transform.getMatrixInversed(),r.start));
	IntersectInfo rawii=this->geometry->testIntersect(rayBeforeTransform);
	ii.isIntersect=rawii.isIntersect;
	if(!(ii.isIntersect)){
		return ii;
	}
	ii.distance=rawii.distance;
	ii.pos=apply(this->transform.getMatrix(),rawii.pos);
	ii.normal=apply(this->transform.getRotation(),rawii.pos);
	return ii;
}