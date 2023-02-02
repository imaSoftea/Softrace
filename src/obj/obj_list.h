#pragma once
#include "../ray/ray.h"
#include "obj.h"
#include <memory>
#include <vector>

class obj_list : public obj
{
public:
	/*_________ Variables _________*/
	std::vector<std::shared_ptr<obj>> objects;

	/*_________ Functions _________*/
	void clear() { objects.clear(); }
	void add(std::shared_ptr<obj> object) { objects.push_back(object); }

	virtual bool hit(const ray& r, float tMin, float tMax, hit_rec& rec) const override;

	/*_________ Constructor _________*/
	obj_list(){}
	obj_list(std::shared_ptr<obj> object) { add(object); }
};

/*_________ Function Definitions _________*/
bool obj_list::hit(const ray& r, float tMin, float tMax, hit_rec& rec) const
{
	hit_rec temprec;
	bool hit_anything = false;
	float closest = tMax;

	for (const auto& object : objects)
	{
		if (object->hit(r, tMin, closest, temprec))
		{
			hit_anything = true;
			closest = temprec.t;
			rec = temprec;
		}
	}

	return hit_anything;
}