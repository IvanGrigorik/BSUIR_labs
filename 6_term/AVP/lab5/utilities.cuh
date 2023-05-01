#pragma once

#define degToRad(val) ((val) *M_PI / 180)

#define CUDA_ASSERT(cudaError)                                                                                         \
    if (cudaError != cudaSuccess) {                                                                                    \
        throw std::runtime_error{cudaGetErrorString(cudaError)};                                                       \
    }
