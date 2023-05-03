#include "Image.cuh"
#include "utilities.cuh"
#include <algorithm>
#include <cmath>

#pragma once

void runCpu(std::string imagePath);

double houghTransform(const ImageCPU &image);