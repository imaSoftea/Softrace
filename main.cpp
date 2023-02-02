#include "src/camera/camera.h"
#include "src/color/materials.h"
#include "src/thread/ctpl_stl.h"
#include <thread>
#include <fstream>
#include <string> 

color ray_color(const ray& r, const obj& world, int depth);
obj_list random_scene();
void drawPixel(
    color p[], int samples_per_pixel, obj_list world, const int maxDepth,
    int i, int j, camera cam, int imgWidth, int imgHeight);

int main()
{
    //Variables
    const auto aspect = 16.0f / 9.0f;
    const int imgWidth = 600;
    const int imgHeight = static_cast<int> (imgWidth / aspect);
    const int samples_per_pixel = 30;
    const int maxDepth = 8;

    // World Variables
    obj_list world = random_scene();

    // Camera
    point3 lookfrom(13.0f, 2.0f, 3.0f);
    point3 lookat(0.0f, 0.0f, 0.0f);
    vec3 vup(0.0f, 1.0f, 0.0f);
    auto dist_to_focus = 10.0f;
    auto aperture = 0.1f;

    camera cam(20.0f, aspect, aperture, dist_to_focus, lookfrom, lookat, vup);

    ctpl::thread_pool threads(std::thread::hardware_concurrency() - 1);

    //Animation Camera
    int frames = 60;

    for (int i = 0; i < frames; i++)
    {
        std::ofstream currentFile;
        std::string fileName = "frames/";
        fileName += std::to_string(i);
        fileName += "frame.ppm";
        std::cout << "File: " << fileName << "\n";

        //Render Process
        currentFile.open(fileName, std::ofstream::out);
        currentFile << "P3\n" << imgWidth << " " << imgHeight << "\n255\n";

        for (int j = imgHeight - 1; j >= 0; --j)
        {
            color p[imgWidth];
            std::vector<std::future<void>> results(imgWidth);

            // Thread Pooling Start
            for (int i = 0; i < imgWidth; ++i)
            {

                results[i] = threads.push([&p, world, i, j, cam, imgHeight](int)
                    {
                        drawPixel(p, samples_per_pixel, world, maxDepth, i, j, cam, imgWidth, imgHeight);
                    });
            }

            // Thread Pooling Line Wait
            for (int i = 0; i < imgWidth; ++i)
            {
                results[i].get();
            }

            // Print Results
            for (color pixel : p)
            {
                write_color(currentFile, pixel, samples_per_pixel);
            }
            std::cerr << "Line: " << j << std::endl;
        }

        cam.movCam(1, .02f);
        cam.movCam(0, -0.2f);
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
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);
        return color(0.0f, 0.0f, 0.0f);
    }

    vec3 direction = r.dir.unitVec();
    auto t = 0.5f * (direction.val[1] + 1.0f);
    direction = ((1.0f - t) * color(1.0f, 1.0f, 1.0f)) + (t * color(0.5f, 0.7f, 1.0f));
    return direction;
}

obj_list random_scene() {
    obj_list world;

    auto ground_material = std::make_shared<lambertian>(color(0.5f, 0.5f, 0.5f));
    world.add(std::make_shared<sphere>(point3(0.0f, -1000.0f, 0.0f), 1000.0f, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_float();
            point3 center(a + 0.9f * random_float(), 0.2f, b + 0.9f * random_float());

            if ((center - point3(4.0f, 0.2f, 0.0f)).length() > 0.9f) {
                std::shared_ptr<material> sphere_material;

                if (choose_mat < 0.8f) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = std::make_shared<lambertian>(albedo);
                    world.add(std::make_shared<sphere>(center, 0.2f, sphere_material));
                }
                else if (choose_mat < 0.95f) {
                    // metal
                    auto albedo = color::random(0.5f, 1.0f);
                    auto fuzz = random_float(0.0f, 0.5f);
                    sphere_material = std::make_shared<metal>(albedo, fuzz);
                    world.add(std::make_shared<sphere>(center, 0.2f, sphere_material));
                }
                else {
                    // glass
                    sphere_material = std::make_shared<dielect>(1.5f);
                    world.add(std::make_shared<sphere>(center, 0.2f, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<dielect>(1.5f);
    world.add(std::make_shared<sphere>(point3(0.0f, 1.0f, 0.0f), 1.0f, material1));

    auto material2 = std::make_shared<lambertian>(color(0.4f, 0.2f, 0.1f));
    world.add(std::make_shared<sphere>(point3(-4.0f, 1.0f, 0.0f), 1.0f, material2));

    auto material3 = std::make_shared<metal>(color(0.7f, 0.6f, 0.5f), 0.0f);
    world.add(std::make_shared<sphere>(point3(4.0f, 1.0f, 0.0f), 1.0f, material3));

    return world;
}

void drawPixel(
    color p[], int samples_per_pixel, obj_list world, const int maxDepth,
    int i, int j, camera cam, int imgWidth, int imgHeight)
{
    color pixel_color = { 0, 0, 0 };
    for (int s = 0; s < samples_per_pixel; ++s) {
        auto u = (i + random_float()) / (imgWidth - 1);
        auto v = (j + random_float()) / (imgHeight - 1);
        ray r = cam.get_ray(u, v);
        pixel_color += ray_color(r, world, maxDepth);
    }

    p[i] = pixel_color;
}