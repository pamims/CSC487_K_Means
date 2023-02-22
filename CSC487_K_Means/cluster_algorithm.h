#ifndef CC_ALGORITHM_H
#define CC_ALGORITHM_H

#include <vector>   // for std::vector<>
#include <utility>  // for std::pair<>
#include "point.h"  // for Point and Centroid




class IClusterAlgorithm {
protected:
	IClusterAlgorithm() {};
public:
	virtual std::pair<std::vector<Point>, std::vector<Centroid>>
		Process(size_t k, std::vector<Point> data) const = 0;
};




class KMeans : public IClusterAlgorithm {
protected:
	std::vector<Point> GetUniqueData(const std::vector<Point>& data) const;
	virtual std::vector<Centroid> GetCentroids(const size_t k, std::vector<Point>& unique_data) const;
public:
	std::pair<std::vector<Point>, std::vector<Centroid>>
		Process(size_t k, std::vector<Point> data) const override;
};

#endif

