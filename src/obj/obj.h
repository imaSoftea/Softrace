#pragma once

#include "../math/vec3.h"
#include "../ray/ray.h"

class material;

struct hit_rec
{
	point3 p;
	vec3 norm;
	float t;
	bool front_face;
	std::shared_ptr<material> mat_ptr;

	inline void set_face_normal(const ray& r, const vec3& outward_normal) {
		front_face = r.dir.dotProd(outward_normal) < 0;
		norm = front_face ? outward_normal : -1 * outward_normal;
	}
};

class obj
{	
public:

	virtual bool hit(const ray& r, float tMin, float tMax, hit_rec& rec) const = 0;

};