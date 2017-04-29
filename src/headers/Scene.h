#ifndef SCENE_H
#define SCENE_H
#include <set>
#include <memory>
#include <utility>
#include "Geometry.h"
#include "Material.h"
#include "Object.h"
#include "Light.h"
#include "Ray.h"
class Scene{
	::std::set<::std::shared_ptr<Object>> objects;
	::std::set<::std::shared_ptr<Light>> lights;
	public:
	inline void addObject(::std::shared_ptr<Object> obj)noexcept{
		objects.insert(obj);
	}
	inline void removeObject(::std::shared_ptr<Object> obj)noexcept{
		objects.erase(obj);
	}
	inline bool hasObject(::std::shared_ptr<Object> obj)const noexcept{
		return objects.find(obj)!=objects.end();
	}
	inline void addLight(::std::shared_ptr<Light> obj)noexcept{
		lights.insert(obj);
	}
	inline void removeLight(::std::shared_ptr<Light> obj)noexcept{
		lights.erase(obj);
	}
	inline bool hasLight(::std::shared_ptr<Light> obj)const noexcept{
		return lights.find(obj)!=lights.end();
	}
	::std::pair<::std::weak_ptr<Material>,IntersectInfo> testIntersect(Ray r)const noexcept;
	::std::pair<::std::weak_ptr<Light>,LightReachInfo> testLightReach(Ray r)const noexcept;
};
#endif //SCENE_H