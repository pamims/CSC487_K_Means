#ifndef CC_IMAGE_MAPPER_H
#define CC_IMAGE_MAPPER_H

#include <utility>
#include <vector>
#include "point.h"
#include "CImg.h"




class ImageConverter {
private:
	ImageConverter();
public:
	static std::vector<Point> BuildData(const cimg_library::CImg<int>& image);
	static cimg_library::CImg<int> BuildImage(const std::vector<Point>& data, size_t width, size_t height);
};

#endif
