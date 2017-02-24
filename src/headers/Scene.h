#ifndef SCENE_H
#define SCENE_H
#include <set>
#include <memory>
#include "Geometry.h"
#include "Object.h"
#include "Ray.h"
class Scene{
	::std::set<::std::shared_ptr<Object>> objects;
	public:
	inline void addObject(::std::shared_ptr<Object> obj)noexcept{
		objects.insert(obj);
	}
	inline void removeObject(::std::shared_ptr<Object> obj)noexcept{
		objects.erase(obj);
	}
	inline bool hasObject(::std::shared_ptr<Object> obj)const noexcept{
		return objects.find(obj)==objects.end();
	}
	IntersectInfo testIntersect(Ray r)const noexcept;
};
#endif //SCENE_H