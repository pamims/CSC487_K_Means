#include <iostream>
#include <vector>
//#include <algorithm>

#include "cluster_algorithm.h"
#include "test.h"
#include "timer.h"
#include "mapper.h"


// tests
void random_colors_test(int k, int width, int height);



int main(int argc, char** argv) {
	random_colors_test(3, 10, 10);

	return 0;
}



void random_colors_test(const int k, const int width, const int height) {
	test::Timer timer;

	std::cout << "Building data set..." << std::endl;
	std::vector<Point> data = test::make_clustered_data_set(k, width, height);
	//std::vector<Point> data = test::make_randomized_data_set(width, height);
	//std::vector<Point> data = test::make_white_data_set(width, height);
	std::cout << "Dataset complete." << std::endl;

	std::cout << "Running k-means on randomized image." << std::endl;
	std::cout << "width  = " << width  << std::endl;
	std::cout << "height = " << height << std::endl;

	KMeans algo;
	timer.Set();
	auto result = algo.Process(k, data);
	auto delta_time = timer.Peek();
	std::vector<Centroid> centroids = result.second;
	
	std::cout << "Processing complete." << std::endl;
	std::cout << "Results: " << std::endl;
	test::print_centroids(centroids);
	std::cout << "Elapsed time: " << delta_time << " seconds.";

	std::vector<Point> mapped_points = Mapper::GetMappedData(result);
	test::print_data_set(mapped_points);

	return;
}