#pragma once
#include "obj.h"

class sphere : public obj
{
public:

	/*_________ Variables & Definitions _________*/
	point3 center;
	float radius {0};
	std::shared_ptr<material> mat_ptr;

	/*_________ Functions_________*/
	virtual bool hit(const ray& r, float tMin, float tMax, hit_rec& rec) const override;

	/*_________ Constructors _________*/
	sphere() = default;
	sphere(point3 c, float r, std::shared_ptr<material> m) : center(c), radius(r), mat_ptr(m) {};

};