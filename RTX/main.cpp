#include <iostream>
#include <fstream>
#include "vec3.h"
#include "color.h"
using std::cout;

int main()
{
	constexpr int IMAGE_WIDTH = 256;
	constexpr int IMAGE_HEIGHT = 256;

	//render image
	std::ofstream image{ "image.ppm" };
	image << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n255\n";
	for (int j = IMAGE_HEIGHT - 1; j >= 0; j--) {
		std::cerr << "\rScanlines remianing: " << j << " " << std::flush;
		for (int i = 0; i < IMAGE_WIDTH; i++) {
			color pixel_color{ double(i) / (IMAGE_WIDTH - 1) , double(j) / (IMAGE_HEIGHT - 1), 0.25 };
			write_color(image, pixel_color);
		}
	}
	image.close();
	std::cerr << "\nDone. \n";
}