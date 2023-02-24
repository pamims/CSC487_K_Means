#ifndef CC_TEST_H
#define CC_TEST_H

#include <vector>
#include "point.h"


namespace test {
	std::vector<Point> make_clustered_data_set(size_t k, size_t width, size_t height);
	std::vector<Point> make_linear_data_set(size_t size);
	std::vector<Point> make_randomized_data_set(size_t width, size_t height);
	std::vector<Point> make_white_data_set(size_t width, size_t height);
	std::vector<Point> make_control_data_set(size_t width, size_t height);
	void print_data_set(const std::vector<Point>& data);
	void print_centroids(const std::vector<Centroid>& centroids);
	void print_elapsed_time(double delta_time);

	namespace speed {
		void   core_algorithm_speed_test();
		double get_controlled_test_result(const size_t k, const size_t width, const size_t height);
	}
}

#endif
