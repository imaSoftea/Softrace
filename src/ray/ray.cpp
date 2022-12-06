#pragma once
#include "ray.h"

// Contains all Class Functions & Overloads for "ray"

/*_________ Functions _________*/

vec3 ray::at(float t) const
{
	return ori + (t * dir);
}


