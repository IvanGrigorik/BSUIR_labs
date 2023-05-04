#pragma once


#define degToRad(val) ((val) *M_PI / 180)

#define CUDA_ASSERT(cudaError)                                                                                         \
    if (cudaError != cudaSuccess) {                                                                                    \
        throw std::runtime_error{cudaGetErrorString(cudaError)};                                                       \
    }

template<typename T>
__device__ T *getRow(T *rowPtr, size_t pitch, unsigned y) {
    return reinterpret_cast<T *>(reinterpret_cast<uint8_t *>(rowPtr) + pitch * y);
}