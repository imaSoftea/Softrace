#pragma once
#include "../math/vec3.h"

class ray
{
public:
		
	/*_________ Variables & Definitions _________*/

	vec3 dir;
	point3 ori;

	/*_________ Functions _________*/

	vec3 at(float t) const;

	/*_________ Constructors _________*/

	ray() {}
	ray(const point3& origin, const vec3& direction) : ori(origin), dir(direction) {}

};