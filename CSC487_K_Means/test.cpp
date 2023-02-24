#include "test.h"

#include <iostream>
#include <random>
#include <fstream>

#include "timer.h"
#include "cluster_algorithm.h"

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



namespace test {
	namespace speed {
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
			return;
		}
	}
}