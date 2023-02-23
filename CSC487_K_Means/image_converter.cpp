#include "image_converter.h"


const unsigned int z = 0;
const unsigned int red_index = 0;
const unsigned int green_index = 1;
const unsigned int blue_index = 2;

const size_t depth = 1;
const size_t color_channels = 3;
const size_t black_pixel = 0;


std::vector<Point> ImageConverter::BuildData(const cimg_library::CImg<int>& image) {

	std::vector<Point> result;
	if (image.is_empty() || image.is_inf() || image.is_nan()) {
		return result;
	}
	const size_t width = static_cast<size_t>(image.width());
	const size_t height = static_cast<size_t>(image.height());
	const size_t size = width * height;
	result.reserve(size);

	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++) {
			int red = image(x, y, z, red_index);
			int green = image(x, y, z, green_index);
			int blue = image(x, y, z, blue_index);

			result.emplace_back(red, green, blue);
		}
	}

	return result;
}

cimg_library::CImg<int> ImageConverter::BuildImage(const std::vector<Point>& data, size_t width, size_t height) {

	cimg_library::CImg<int> result(width, height, depth, color_channels, black_pixel);

	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++) {
			size_t index = x + width * y;
			result(x, y, z, red_index) = data[index].Red();
			result(x, y, z, green_index) = data[index].Green();
			result(x, y, z, blue_index) = data[index].Blue();
		}
	}

	return result;
}