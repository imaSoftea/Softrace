#pragma once
#include "../math/vec3.h"
#include <iostream>

void write_color(std::ostream& out, color pixel, int samples_per_pixel)
{
    auto r = pixel.val[0];
    auto g = pixel.val[1];
    auto b = pixel.val[2];

    auto scale = 1.0f / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    out << static_cast<int>(256 * clamp(r, 0.0f, 0.999f)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0f, 0.999f)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0f, 0.999f)) << '\n';
}
