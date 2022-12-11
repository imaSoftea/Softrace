#pragma once

#include <iostream>
#include "../color/color.h"
#include "../obj/obj_list.h"
#include "../obj/sphere.h"

class camera
{
public:
	camera(float fov, float aspect, float apperature, float focus, point3 from, point3 at, vec3 up)
	{
        auto theta = fov * (pi / 180.0f);
        auto h = tan(theta / 2.0f);

        const int imgWidth = 400;
        const int imgHeight = static_cast<int> (imgWidth / aspect);

        auto viewport_height = 2.0f * h;
        auto viewport_width = aspect * viewport_height;
        auto focal_length = 1.0f;

        w = (from - at).unitVec();
        u = up.crossProd(w).unitVec();
        v = w.crossProd(u);

        origin = from;
        horizontal = focus * viewport_width * u;
        vertical = focus * viewport_height * v;
        lowerleftcorner = origin - horizontal/2 - vertical/2 - focus * w;
        len = apperature/ 2;
    }

    ray get_ray(float s, float t) const
    {
        vec3 rd = len * vec3::random_in_unit_disk();
        vec3 offset = u * rd.val[0] + v * rd.val[1];

        return ray(origin + offset, lowerleftcorner + s * horizontal + t * vertical - origin - offset);
    }

    private:

        point3 origin;
        point3 lowerleftcorner;
        vec3 horizontal;
        vec3 vertical;

        vec3 u, v, w;
        float len;
};