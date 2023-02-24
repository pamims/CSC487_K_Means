#include "cluster_algorithm.h"

//#include <iostream>
#include <algorithm>
#include <execution>
#include <mutex>
#include "project_constants.h"

#include <random>
#include <ctime>

#include "test.h"
#include "timer.h"


inline size_t clamp_k(const size_t k) {
	if (k < default_min_k)
		return default_min_k;
	if (k > default_max_k)
		return default_max_k;
	return k;
}

std::pair<std::vector<Point>, std::vector<Centroid>>
KMeans::Process(const size_t _k, std::vector<Point> data) const {

	if (data.empty()) {
		auto result = std::make_pair(data, std::vector<Centroid>());
		return result;
	}

	const size_t temp_k = clamp_k(_k);
	auto unique_data = GetUniqueData(data);
	auto centroids = GetCentroids(temp_k, unique_data);
	const size_t k = centroids.size();
	//std::mutex centroids_mutex;

	unsigned int iterations = 0;
	do {
		auto put_data_in_buckets = [centroids, k](Point& point) {
			int sq_distance = Point::BeyondMaxSquaredDistance;
			int i = 0;
			do {
				int temp_sq_distance = centroids[i].SquaredDistance(point);
				if (temp_sq_distance < sq_distance) {
					sq_distance = temp_sq_distance;
					point.SetBucket(i);
				}
				i++;
			} while (i < k);
		};
		auto zero_centroids = [](Centroid& centroid) {
			centroid.Zero();
		};
		// Mutex collisions too high experimentally.
		auto sum_up_values = [&centroids/*, &centroids_mutex*/](const Point& point) { // not thread safe
			int index = point.GetBucket();
			//centroids_mutex.lock();
			centroids[index].AddPoint(point);
			//centroids_mutex.unlock();
		};
		auto set_centroid_values = [](Centroid& centroid) {
			centroid.SetToAveragePointValue();
		};


		std::vector<Centroid> previous_centroids = centroids;
		std::for_each(std::execution::par, data.begin(), data.end(), put_data_in_buckets);
		std::for_each(std::execution::par, centroids.begin(), centroids.end(), zero_centroids);
		std::for_each(std::execution::seq, data.begin(), data.end(), sum_up_values); // not thread safe
		std::for_each(std::execution::par, centroids.begin(), centroids.end(), set_centroid_values);

		bool centroids_stayed_the_same = std::equal(
			std::execution::par,
			previous_centroids.begin(),
			previous_centroids.end(),
			centroids.begin(),
			centroids.end()
		);

		if (centroids_stayed_the_same) {
			break;
		}

		iterations++;
	} while (iterations > default_max_iterations);

	auto unused_centroids = std::remove_if(
		std::execution::par,
		centroids.begin(),
		centroids.end(),
		[](const Centroid& centroid) {
			return centroid.IsUnused();
		}
	);
	centroids.erase(unused_centroids, centroids.end());

	auto result = std::make_pair(data, centroids);
	return result;
}

std::vector<Point> KMeans::GetUniqueData(const std::vector<Point>& data) const {
	std::vector<Point> copy = data;
	std::sort(copy.begin(), copy.end());
	auto last = std::unique(copy.begin(), copy.end());
	copy.erase(last, copy.end());
	return copy;
}

std::vector<Centroid> KMeans::GetCentroids(const size_t _k, std::vector<Point>& unique_data) const {
	// k cannot be larger than the set of unique colors.
	static std::mt19937 random_generator(static_cast<unsigned int>(time(nullptr)));

	const size_t num_points = unique_data.size();
	const size_t k = (_k < num_points) ? _k : num_points;

	std::vector<Centroid> result;
	result.reserve(k);

	std::shuffle(unique_data.begin(), unique_data.end(), random_generator);
	for (size_t i = 0; i < k; i++) {
		result.emplace_back(unique_data[i]);
	}

	return result;
}





std::pair<std::vector<Point>, std::vector<Centroid>>
KMeansUnweighted::Process(const size_t _k, std::vector<Point> data) const {

	if (data.empty()) {
		auto result = std::make_pair(data, std::vector<Centroid>());
		return result;
	}

	const size_t temp_k = clamp_k(_k);
	auto unique_data = GetUniqueData(data);
	auto centroids = GetCentroids(temp_k, unique_data);
	const size_t k = centroids.size();
	//std::mutex centroids_mutex;

	unsigned int iterations = 0;
	do {
		auto put_data_in_buckets = [centroids, k](Point& point) {
			int sq_distance = Point::BeyondMaxSquaredDistance;
			int i = 0;
			do {
				int temp_sq_distance = centroids[i].SquaredDistance(point);
				if (temp_sq_distance < sq_distance) {
					sq_distance = temp_sq_distance;
					point.SetBucket(i);
				}
				i++;
			} while (i < k);
		};
		auto zero_centroids = [](Centroid& centroid) {
			centroid.Zero();
		};
		// Mutex collisions too high experimentally.
		auto sum_up_values = [&centroids/*, &centroids_mutex*/](const Point& point) { // not thread safe
			int index = point.GetBucket();
			//centroids_mutex.lock();
			centroids[index].AddPoint(point);
			//centroids_mutex.unlock();
		};
		auto set_centroid_values = [](Centroid& centroid) {
			centroid.SetToAveragePointValue();
		};


		std::vector<Centroid> previous_centroids = centroids;
		std::for_each(std::execution::par, unique_data.begin(), unique_data.end(), put_data_in_buckets);
		std::for_each(std::execution::par, centroids.begin(), centroids.end(), zero_centroids);
		std::for_each(std::execution::seq, unique_data.begin(), unique_data.end(), sum_up_values); // not thread safe
		std::for_each(std::execution::par, centroids.begin(), centroids.end(), set_centroid_values);

		bool centroids_stayed_the_same = std::equal(
			std::execution::par,
			previous_centroids.begin(),
			previous_centroids.end(),
			centroids.begin(),
			centroids.end()
		);

		if (centroids_stayed_the_same) {
			break;
		}

		iterations++;
	} while (iterations > default_max_iterations);

	auto put_data_in_buckets = [centroids, k](Point& point) {
		int sq_distance = Point::BeyondMaxSquaredDistance;
		int i = 0;
		do {
			int temp_sq_distance = centroids[i].SquaredDistance(point);
			if (temp_sq_distance < sq_distance) {
				sq_distance = temp_sq_distance;
				point.SetBucket(i);
			}
			i++;
		} while (i < k);
	};
	std::for_each(std::execution::par, data.begin(), data.end(), put_data_in_buckets);

	auto unused_centroids = std::remove_if(
		std::execution::par,
		centroids.begin(),
		centroids.end(),
		[](const Centroid& centroid) {
			return centroid.IsUnused();
		}
	);
	centroids.erase(unused_centroids, centroids.end());

	auto result = std::make_pair(data, centroids);
	return result;
}
