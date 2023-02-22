#ifndef CC_TEST_H
#define CC_TEST_H

#include <vector>
#include "point.h"


namespace test {
	std::vector<Point> make_clustered_data_set(int k, int width, int height);
	std::vector<Point> make_linear_data_set(int size);
	std::vector<Point> make_randomized_data_set(int width, int height);
	std::vector<Point> make_white_data_set(int width, int height);
	void print_data_set(const std::vector<Point>& data);
	void print_centroids(const std::vector<Centroid>& centroids);
}

#endif