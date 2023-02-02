#pragma once
#include "sphere.h"

bool sphere::hit(const ray& r, float tMin, float tMax, hit_rec& rec) const
{
	vec3 oc = r.ori - center;
	auto a = r.dir.lengthSquared();
	auto bHalf = oc.dotProd(r.dir);
	auto c = oc.lengthSquared() - radius * radius;
	auto discrim = bHalf * bHalf - a * c;

	if (discrim < 0) return false;
	auto sqrtd = sqrt(discrim);

    auto root = (-bHalf - sqrtd) / a;
    if (root < tMin || tMax < root) {
        root = (-bHalf + sqrtd) / a;
        if (root < tMin || tMax < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}

