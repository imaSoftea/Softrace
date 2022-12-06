#pragma once

#include <iostream>
#include "../color/color.h"
#include "../obj/obj_list.h"
#include "../obj/sphere.h"

class camera
{
public:
	camera()
	{
        const auto aspect = 16.0f / 9.0f;
        const int imgWidth = 400;
        const int imgHeight = static_cast<int> (imgWidth / aspect);

        auto viewport_height = 2.0f;
        auto viewport_width = aspect * viewport_height;
        auto focal_length = 1.0f;


        origin = point3(0, 0, 0);
        horizontal = vec3(viewport_width, 0, 0);
        vertical = vec3(0, viewport_height, 0);
        lowerleftcorner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);
    }

    ray get_ray(float u, float v) const
    {
        return ray(origin, lowerleftcorner + u * horizontal + v * vertical - origin);
    }

    private:

        point3 origin;
        point3 lowerleftcorner;
        vec3 horizontal;
        vec3 vertical;
};