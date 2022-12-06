#include "src/camera/camera.h"

color ray_color(const ray& r, const obj& world, int depth);

int main()
{
	//Variables

    const auto aspect = 16.0f / 9.0f;
	const int imgWidth = 900;
    const int imgHeight = static_cast<int> (imgWidth / aspect);
    const int samples_per_pixel = 100;
    const int maxDepth = 50;

    // World Variables

    obj_list world;
    world.add(std::make_shared<sphere>(point3(0.0f, 0.0f, -1.0f), 0.5f));
    world.add(std::make_shared<sphere>(point3(0.0f, -100.5f, -1.0f), 100.0f));

    // Camera

    camera cam;

    //Render Process

	std::cout << "P3\n" << imgWidth << " " << imgHeight << "\n255\n";

    for (int j = imgHeight - 1; j >= 0; --j)
    {   
        for (int i = 0; i < imgWidth; ++i)
        {

            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_float()) / (imgWidth - 1);
                auto v = (j + random_float()) / (imgHeight - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, maxDepth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
        std::cerr << "Line: " << j << std::endl;
    }
    return 0;
}

color ray_color(const ray& r, const obj& world, int depth)
{
    hit_rec rec;

    if (depth <= 0)
        return color(0, 0, 0);  

    if (world.hit(r, 0.001f, infinity, rec))
    {
        point3 target = rec.p + rec.norm + vec3::random_unit_vector();
        return 0.5f * ray_color(ray(rec.p, target - rec.p), world, depth-1);
    }

    vec3 direction = r.dir.unitVec();
    auto t = 0.5f * (direction.val[1] + 1.0f);
    direction = ((1.0f - t) * color(1.0f, 1.0f, 1.0f)) + (t * color(0.5f, 0.7f, 1.0f));
    return direction;
}