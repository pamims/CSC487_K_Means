#ifndef CC_PROJECT_CONSTANTS_H
#define CC_PROJECT_CONSTANTS_H

#include <limits>
#include <cstdint>

constexpr int max_color_value = static_cast<int>(std::numeric_limits<uint8_t>::max());
constexpr int max_image_size = std::numeric_limits<int>::max() / max_color_value;

constexpr unsigned int default_max_iterations = 1000;
constexpr size_t default_min_k = 1;
constexpr size_t default_max_k = 255;

constexpr size_t one_byte = sizeof(uint8_t);
constexpr size_t two_bytes = 2 * one_byte;
constexpr size_t three_bytes = 3 * one_byte;


#endif