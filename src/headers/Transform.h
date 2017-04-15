#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <cmath>
#include <ostream>
#include "Vector3.h"
#include "Matrix4.h"
#include "Quaternion.h"

class Transform{
	Vector3 position;
	Quaternion rotation;
	Matrix4 matrix;
	Matrix4 matrixInversed;
	inline void update()noexcept{
		this->matrix=Matrix4::fromTranslation(position)*Matrix4::fromQuaternion(rotation);
		this->matrixInversed=matrix.inversed();
	}
	public:
	Transform(Vector3 position=Vector3(0,0,0),Quaternion rotation=Quaternion())noexcept:position(position),rotation(rotation){
		this->update();
	}
	inline Vector3 getPosition()const noexcept{
		return this->position;
	}
	inline void setPosition(Vector3 position)noexcept{
		this->position=position;
		this->update();
	}
	inline Quaternion getRotation()const noexcept{
		return this->rotation;
	}
	inline void setRotation(Quaternion rotation)noexcept{
		this->rotation=rotation.normalized();
		this->update();
	}
	inline Matrix4 getMatrix()const noexcept{
		return this->matrix;
	}
	inline Matrix4 getMatrixInversed()const noexcept{
		return this->matrixInversed;
	}
};

#endif //TRANSFORM_H