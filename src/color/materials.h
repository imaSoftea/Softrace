#pragma once
#include "../math/vec3.h"
#include "../ray/ray.h"
#include "../obj/obj.h"

class material 
{
public:
	virtual bool scatter(const ray& rin, const hit_rec& rec, color& attenuation, ray& scattered) const = 0;
};

class lambertian : public material
{
public:

	color albedo;

	virtual bool scatter(const ray& rin, const hit_rec& rec, color& attenuation, ray& scattered) const override
	{
		auto scatDir = rec.norm + vec3::random_unit_vector();

		// Catch degenerate scatter direction
		if (scatDir.near_zero())
			scatDir = rec.norm;

		scattered = ray(rec.p, scatDir);
		attenuation = albedo;
		return true;
	}

	lambertian(const color& a) : albedo(a) {}
};

class metal : public material
{
public:
	color albedo;
	float fuzz;

	virtual bool scatter(const ray& rin, const hit_rec& rec, color& attenuation, ray& scattered) const override
	{
		vec3 reflected = vec3::reflect(rin.dir.unitVec(), rec.norm);
		scattered = ray(rec.p, reflected + fuzz* vec3::random_in_unit_sphere());
		attenuation = albedo;
		return scattered.dir.dotProd(rec.norm) > 0;
	}


	metal(const color &a, float f) : albedo(a), fuzz(f < 1 ? f : 1) {}
};

class dielect : public material
{
public:
	float ir;

	virtual bool scatter(const ray& rin, const hit_rec& rec, color& attenuation, ray& scattered) const override
	{
		attenuation = color(1.0f, 1.0f, 1.0f);
		float ratio = rec.front_face ? (1.0f / ir) : ir;

		vec3 unitDir = rin.dir.unitVec();
		float cos = fmin(rec.norm.dotProd(-1 * unitDir), 1.0f);
		float sin = sqrt(1.0f - cos*cos);

		bool noRefract = ratio * sin > 1.0f;
		vec3 dir = (noRefract || reflectance(cos, ratio) > random_float()) ?
			vec3::reflect(unitDir,rec.norm) : vec3::refract(unitDir, rec.norm, ratio);

		scattered = ray(rec.p, dir);
		return true;
	}

	dielect(float i) : ir(i) {}

private:
	static float reflectance(float cos, float ref)
	{
		auto r = (1.0f - ref) / (1.0f + ref);
		r *= r;
		return r + (1.0f - r) * pow(1.0f - cos, 5.0f);
	}
};