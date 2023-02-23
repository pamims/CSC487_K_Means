#include "test.h"

#include <iostream>
#include <random>

namespace test {
	static std::mt19937 rand_gen(static_cast<int>(time(nullptr)));

	std::vector<Point> make_clustered_data_set(size_t k, size_t width, size_t height) {

		size_t size = width * height;
		size_t delta_target = 255 / k;

		size_t variance = 2 + (delta_target / 8);
		//variance = 0;

		std::vector<Point> data;
		data.reserve(size);

		for (size_t i = 0, d = 0; i < size; i++, d = (d + 1) % k) {

			size_t target = d * delta_target;
			size_t value = target + (rand_gen() % variance);

			data.emplace_back(value, value, value);
		}

		return data;
	}

	std::vector<Point> make_randomized_data_set(size_t width, size_t height) {

		size_t size = width * height;

		std::vector<Point> data;
		data.reserve(size);

		for (size_t i = 0; i < size; i++) {
			int red = rand_gen() % 255;
			int green = rand_gen() % 255;
			int blue = rand_gen() % 255;

			data.emplace_back(red, green, blue);
		}

		return data;
	}

	std::vector<Point> make_linear_data_set(size_t size) {
		std::vector<Point> data;
		data.reserve(size);

		for (size_t i = 0; i < size; i++) {
			data.emplace_back(i, 0, 0);
		}
		return data;
	}

	std::vector<Point> make_control_data_set(size_t width, size_t height) {
		const unsigned int seed = 147;
		const unsigned int a = 1664525;
		const unsigned int c = 1013904223;
		unsigned int X = seed;

		size_t size = width * height;
		std::vector<Point> data;
		data.reserve(size);

		for (size_t i = 0; i < size; i++) {
			int red = X % 256;
			X = a * X + c;
			int green = X % 256;
			X = a * X + c;
			int blue = X % 256;
			X = a * X + c;
			data.emplace_back(red, green, blue);
		}

		data[width].Print();

		return data;
	}

	std::vector<Point> make_white_data_set(size_t width, size_t height) {
		size_t size = width * height;
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

	void print_elapsed_time(double delta_time) {
		std::cout << "Elapsed time: " << delta_time << "seconds." << std::endl;
	}
}