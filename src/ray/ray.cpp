#pragma once
#include "ray.h"

// Contains all Class Functions & Overloads for "ray"

/*_________ Functions _________*/

vec3 ray::at(float t) const
{
	return ori + (t * dir);
}

// Contains all Utillity Functions & Overloads for "ray"
	
/*_________ Functions _________*/

color ray_color(const ray& r)
{
	auto t = hit_sphere(point3(0, 0, -1), 0.5f, r);
	if(t > 0.0f)
	{
		vec3 n = (r.at(t) - vec3(0, 0, -1));
		n = n.unitVec();

		return 0.5 * color(n.val[0]+1, n.val[1]+1, n.val[2]+1);
	}

	vec3 direction = r.dir.unitVec();
	t = 0.5f * (direction.val[1] + 1.0f);
	direction =  ((1.0f - t) * color(1.0f, 1.0f, 1.0f)) + (t * color(0.5f, 0.7f, 1.0f));
	return direction;
}

float hit_sphere(const point3& center, float radius, const ray& r)
{
	vec3 oc = r.ori - center;
	auto a = r.dir.lengthSquared();
	auto bHalf = oc.dotProd(r.dir);
	auto c = oc.lengthSquared() - radius * radius;
	auto discrim = bHalf * bHalf - a * c;
	
	if (discrim < 0)
	{
		return -1.0f;
	}
	else
	{
		return (-bHalf - sqrt(discrim)) /  a;
	}
}
