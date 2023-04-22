#include "Image.cuh"
#include <algorithm>
#include <cmath>
#define degToRad(val) ((val) *M_PI / 180)

#pragma once

void runCpu(std::string imagePath);