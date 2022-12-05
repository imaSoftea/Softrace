#pragma once
#include "../math/vec3.h"
#include <iostream>

void write_color(std::ostream& out, vec3 color)
{
	out << static_cast<int>(255.999 * color.val[0]) << ' '
		<< static_cast<int>(255.999 * color.val[1]) << ' '
		<< static_cast<int>(255.999 * color.val[2]) << std::endl;
}
