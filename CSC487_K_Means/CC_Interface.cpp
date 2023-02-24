#include "CC_Interface.h"

#include <thread>
#include <memory>
#include "cluster_algorithm.h"
#include "image_converter.h"
#include "mapper.h"
#include "project_constants.h"

//remove later
//#include <iostream>


std::unique_ptr<IClusterAlgorithm> GetAlgorithm(CC_AlgorithmType algorithm_type);
void DisplayImage(const unsigned int x, const unsigned int y, const cimg_library::CImg<int>& image, cimg_library::CImgDisplay& display, const char* title);

void CC_Interface::Process(const char *filename, unsigned int k, CC_AlgorithmType algorithm_type) {

	std::unique_ptr<IClusterAlgorithm> algorithm = GetAlgorithm(algorithm_type);
	if (algorithm.get() == nullptr) {
		return;
	}

	original_image = cimg_library::CImg<int>(filename);

	const unsigned int width = original_image.width();
	const unsigned int height = original_image.height();

	auto data = ImageConverter::BuildData(original_image);
	auto result_pair = algorithm->Process(static_cast<size_t>(k), data);
	auto result_data = DataMapper::BuildData(result_pair);

	result_image = ImageConverter::BuildImage(result_data, width, height);

	return;
}

void CC_Interface::Display() {
	DisplayImage(0, 0, original_image, original_display, "Original Image");
	DisplayImage(0, 0, result_image, result_display, "Processed Image");
}

void CC_Interface::Close() {
	//original_display.close();
	//result_display.close();
	original_display.assign();
	result_display.assign();
}

void CC_Interface::Save(const char *filename, CC_FileType filetype) const {
	
	switch (filetype) {
	case CC_FileType::bmp:
		result_image.save_bmp(filename);
		return;
	case CC_FileType::jpeg:
		result_image.save_jpeg(filename);
		return;
	case CC_FileType::png:
		result_image.save_png(filename);
		return;
	default:
		return;
	}

	return;
}

bool CC_Interface::CanSave() const noexcept {
	return !result_image.is_empty();
}


std::unique_ptr<IClusterAlgorithm> GetAlgorithm(CC_AlgorithmType algorithm_type) {
	std::unique_ptr<IClusterAlgorithm> algorithm;

	switch (algorithm_type) {
	case CC_AlgorithmType::kMeansUnweighted:
		algorithm = std::make_unique<KMeansUnweighted>();
		break;
	case CC_AlgorithmType::kMedians:	//not yet implemented
		[[fallthrough]];
	case CC_AlgorithmType::kpp:			//not yet implemented
		[[fallthrough]];
	case CC_AlgorithmType::kMeans:
		algorithm = std::make_unique<KMeans>();
		break;
	default:
		algorithm = std::make_unique<KMeans>();
	}

	return algorithm;
}

void DisplayImage(
	const unsigned int x,
	const unsigned int y,
	const cimg_library::CImg<int>& image,
	cimg_library::CImgDisplay& display,
	const char* title)
{

	unsigned int width = image.width();
	unsigned int height = image.height();

	float f_width = static_cast<float>(width);
	float f_height = static_cast<float>(height);
	float aspect_ratio = f_width / f_height;

	float target_width = max_display_size;
	float target_height = max_display_size;

	if (aspect_ratio > 1.0) {
		target_height = target_height / aspect_ratio;
	}
	else if (aspect_ratio < 1.0) {
		target_width = target_width * aspect_ratio;
	}

	f_width = target_width;
	f_height = target_height;

	width = static_cast<unsigned int>(f_width);
	height = static_cast<unsigned int>(f_height);

	display.assign(width, height, title, 0, false, false);
	display.move(x, y);
	display.display(image);
	return;
}