#include <iostream>
#include "src/math/vec3.h"
#include "src/color/color.h"
#include "src/ray/ray.h"

int main()
{
	//Variables

    const auto aspect = 16.0f / 9.0f;
	const int imgWidth = 400;
    const int imgHeight = static_cast<int> (imgWidth / aspect);

    // Camera

    auto viewport_height = 2.0f;
    auto viewport_width = aspect * viewport_height;
    auto focal_length = 1.0f;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    //Render Process

	std::cout << "P3\n" << imgWidth << " " << imgHeight << "\n255\n";

    for (int j = imgHeight - 1; j >= 0; --j)
    {   
        for (int i = 0; i < imgWidth; ++i)
        {

            //Progress
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

            auto u = float(i) / (imgWidth - 1);
            auto v = float(j) / (imgHeight - 1);

            ray r(origin, lower_left_corner + (u*horizontal) + (v*vertical) - origin);

            color curPixel = ray_color(r);
            write_color(std::cout, curPixel);
        }
    }
}