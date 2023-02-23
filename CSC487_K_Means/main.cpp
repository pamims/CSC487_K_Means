#include <iostream>
#include <fstream>
#include <vector>

#include "cluster_algorithm.h"
#include "test.h"
#include "timer.h"
#include "mapper.h"
#include "image_converter.h"
#include "CImg.h"

// because I'm lazy
#include <string>


// speed tests
void   core_algorithm_speed_test();
double get_controlled_test_result(const size_t k, const size_t width, const size_t height);


// -- MAIN -- //
int main(int argc, char** argv) {
	if (argc < 2) {
		std::cout << "No image supplied" << std::endl;
		return 0;
	}

	std::string filename = argv[1];
	cimg_library::CImg<int> image(filename.c_str());
	const size_t width = image.width();
	const size_t height = image.height();
	std::cout << width << " : " << height << std::endl;
	
	auto data = ImageConverter::BuildData(image);
	KMeans algorithm;
	auto result = algorithm.Process(10, data);
	data = Mapper::GetMappedData(result);

	auto new_image = ImageConverter::BuildImage(data, width, height);
	filename += ".result.bmp";
	new_image.save_bmp(filename.c_str());

	return 0;
}
// ---------- //


// speed test definitions
double get_controlled_test_result(const size_t k, const size_t width, const size_t height) {
	test::Timer timer;

	timer.Set();
	std::vector<Point> data = test::make_control_data_set(width, height);
	double build_time = timer.Peek();

	KMeans algorithm;

	timer.Set();
	auto result = algorithm.Process(k, data);
	double process_time = timer.Peek();
	std::vector<Centroid> centroids = result.second;

	std::cout << "Elapsed time: " << process_time << " seconds." << std::endl;

	return process_time;
}

void core_algorithm_speed_test() {
	std::ofstream out_file;

	std::cout << "Opening test_results.txt" << std::endl;
	out_file.open("test_results.txt");
	if (!out_file.is_open()) {
		std::cout << "Problem opening output file." << std::endl;
		return;
	}

	test::Timer timer;
	timer.Set();
	for (int i = 0; i < 1000; i++) {
		std::cout << "Begin test runs and collect results: " << i + 1 << "/" << 1000 << " : " << timer.Peek() << " seconds elapsed." << std::endl;
		double result = get_controlled_test_result(255, 500, 500);
		out_file << result << std::endl;
	}

	out_file.close();

	std::cout << "Data collection is complete.";
}