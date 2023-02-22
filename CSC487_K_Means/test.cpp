#include "test.h"

#include <iostream>
#include <random>

namespace test {
	static std::mt19937 rand_gen(static_cast<int>(time(nullptr)));

	std::vector<Point> make_clustered_data_set(int k, int width, int height) {

		int size = width * height;
		int delta_target = 255 / k;

		int variance = 2 + (delta_target / 8);
		//variance = 0;

		std::vector<Point> data;
		data.reserve(size);

		for (int i = 0, d = 0; i < size; i++, d = (d + 1) % k) {

			int target = d * delta_target;
			int value = target + (rand_gen() % variance);

			data.emplace_back(value, value, value);
		}

		return data;
	}

	std::vector<Point> make_randomized_data_set(int width, int height) {

		int size = width * height;

		std::vector<Point> data;
		data.reserve(size);

		for (int i = 0; i < size; i++) {
			int red = rand_gen() % 255;
			int green = rand_gen() % 255;
			int blue = rand_gen() % 255;

			data.emplace_back(red, green, blue);
		}

		return data;
	}

	std::vector<Point> make_linear_data_set(int size) {
		std::vector<Point> data;
		data.reserve(size);

		for (int i = 0; i < size; i++) {
			data.emplace_back(i, 0, 0);
		}
		return data;
	}

	std::vector<Point> make_white_data_set(int width, int height) {
		int size = width * height;
		std::vector<Point> data;
		data.reserve(size);

		for (int i = 0; i < size; i++) {
			data.emplace_back(255, 255, 255);
		}
		return data;
	}

	void print_data_set_sample(const std::vector<Point>& data) {

		size_t size = data.size();

		for (int i = 0; i < 100; i++) {
			int index = rand_gen() % size;
			data[index].Print();
		}

		return;
	}

	void print_data_set(const std::vector<Point>& data) {
		for (Point point : data) {
			point.Print();
		}
	}

	void print_centroids(const std::vector<Centroid>& centroids) {
		std::cout << "------" << std::endl;
		for (Centroid centroid : centroids) {
			centroid.Print();
		}
		std::cout << "------" << std::endl;
	}
}