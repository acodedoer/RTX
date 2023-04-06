#include <iostream>
#include <fstream>
#include "rtx.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"

using std::cout;

color ray_color(const ray& r, const hittable& world)
{
	hit_record rec;
	if (world.hit(r, 0, infinity, rec))
	{
		return 0.5 * (rec.normal + color(1, 1, 1));
	}

	vec3 unit_direction = unit_vector(r.get_direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
	// Image
	constexpr int IMAGE_WIDTH = 400;
	constexpr auto ASPECT_RATIO = 16.0 / 9.0;
	constexpr int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO);

	//World
	hittable_list world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

	// Camera
	auto viewport_height = 2.0;
	auto viewport_width = ASPECT_RATIO * viewport_height;
	auto focal_length = 1.0;

	auto origin = point3(0, 0, 0);
	auto horizontal = vec3(viewport_width, 0, 0);
	auto vertical = vec3(0, viewport_height, 0);
	auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

	//render image
	std::ofstream image{ "image.ppm" };
	image << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n255\n";
	for (int j = IMAGE_HEIGHT - 1; j >= 0; j--) {
		std::cerr << "\rScanlines remianing: " << j << " " << std::flush;
		for (int i = 0; i < IMAGE_WIDTH; i++) {
			auto u = double(i) / (IMAGE_WIDTH - 1);
			auto v = double(j) / (IMAGE_HEIGHT - 1);
			ray r{ origin, lower_left_corner + u * horizontal + v * vertical - origin };
			color pixel_color = ray_color(r, world);
			write_color(image, pixel_color);
		}
	}
	image.close();
	std::cerr << "\nDone. \n";
}