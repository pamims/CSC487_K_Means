#ifndef CC_MAPPER_H
#define CC_MAPPER_H

#include <utility>
#include <vector>
#include "point.h"




class Mapper {
private:
	Mapper();
public:
	std::pair<int, int> a;
	static std::vector<Point> GetMappedData(const std::pair<std::vector<Point>, std::vector<Centroid>>& input);
};

#endif

