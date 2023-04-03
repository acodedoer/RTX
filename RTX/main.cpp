#include <iostream>
#include <fstream>
#include "vec3.h"
#include "color.h"
#include "ray.h"
using std::cout;

bool hit_sphere(const point3& center, double radius, const ray& r)
{
	vec3 oc = r.get_origin() - center;
	auto a = dot(r.get_direction(), r.get_direction());
	auto b = 2.0 * dot(oc, r.get_direction());
	auto c = dot(oc, oc) - radius * radius;
	auto discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}

color ray_color(const ray& r)
{
	if (hit_sphere(point3(0, 0, -1), 0.5, r))
		return color(1, 0, 0);
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
			write_color(image, ray_color(r));
		}
	}
	image.close();
	std::cerr << "\nDone. \n";
}