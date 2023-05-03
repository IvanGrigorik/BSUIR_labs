#include "Image.cuh"
#include "cpu.cuh"
#include "utilities.cuh"
#include <iostream>
#include <thrust/device_vector.h>
#include <thrust/execution_policy.h>
#include <thrust/reduce.h>

using namespace std;

// Hough ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

__device__ GPUPixel markerGPU{0, 255, 0};
__device__ GPUPixel thresholdGPU{20, 20, 20};

__global__ void houghKernel(const ImageGPU image, int *houghAccum,//NOLINT (to disable clang-tidy)
                            float step, int thetasCount, int maxDist) {
    const unsigned x = threadIdx.x + blockDim.x * blockIdx.x;
    const unsigned y = threadIdx.y + blockDim.y * blockIdx.y;

    if (y >= image.height or x >= image.width) {
        return;
    }
    //    if(x == 20)

    auto row = getRow(image.devData, image.pitch, y);
    auto element = row[x];
    //    printf("x:%d y:%d: %d:%d:%d\n", x, y, element.red, element.green, element.blue);

    if (abs(element.red - markerGPU.red) >= thresholdGPU.red or      //
        abs(element.green - markerGPU.green) >= thresholdGPU.green or//
        abs(element.blue - markerGPU.blue) >= thresholdGPU.blue) {
        return;
    }

    double ang = -90;
    for (int h = 0; h < thetasCount; ang += step, h++) {
        int idx = static_cast<int>(maxDist + x * cos(degToRad(ang)) + y * sin(degToRad(ang)));
        atomicAdd(&houghAccum[thetasCount * idx + h], 1);
        //        if (idx == 44 and h == 60) {
        //            printf("X:Y: %d:%d\n", x, y);
        //        }
    }
}

double houghGPU(const ImageGPU &image, const dim3 numBlocks, const dim3 threadsPerBlock) {
    int *houghAccum;
    const int maxDist = static_cast<int>(round(sqrt(pow(image.height, 2) + pow(image.width, 2))));
    const int thetasCount = 2 * (image.height + image.width) - 4;

    auto accumLen = 2 * maxDist * thetasCount;
    CUDA_ASSERT(cudaMallocManaged(&houghAccum, accumLen * sizeof(int)))
    CUDA_ASSERT(cudaMemset(houghAccum, 0, accumLen * sizeof(int)))

    const float step = 180.f / static_cast<float>(thetasCount);

    houghKernel<<<numBlocks, threadsPerBlock>>>(image, houghAccum, step, thetasCount, maxDist);
    CUDA_ASSERT(cudaDeviceSynchronize())

    int idx{}, max{};
    for (int i = 0; i < maxDist * 2; i++) {
        for (int j = 0; j < thetasCount; j++) {
            if (houghAccum[i * thetasCount + j] > max) {
                max = houghAccum[i * thetasCount + j];
                idx = j;
            }
        }
    }

    auto angle = -90 + step * static_cast<float>(idx);
    return angle;
}


// Rotation ///////////////////////////////////////////////////////////////////////////////////////////////////////////
__global__ void rotateKernel(const ImageGPU sourceImage, ImageGPU destinationImage,//NOLINT (to disable clang-tidy)
                             const double k1, const double k2, const int centerX, const int centerY) {
    // Cast, 'cause need sign to further calculations
    const int x = static_cast<int>(threadIdx.x + blockDim.x * blockIdx.x);
    const int y = static_cast<int>(threadIdx.y + blockDim.y * blockIdx.y);

    if (y >= sourceImage.height or x >= sourceImage.width or y >= destinationImage.height or
        x >= destinationImage.width) {
        return;
    }

    int newX = static_cast<int>(k1 * (x - centerX) + k2 * (y - centerY) + centerX);
    int newY = static_cast<int>(k1 * (y - centerY) - k2 * (x - centerX) + centerY);

    if (newX < 0 or newX >= sourceImage.width or newY < 0 or newY >= sourceImage.height) {
        return;
    }


    auto srcRow = getRow(sourceImage.devData, sourceImage.pitch, y);
    auto sourceElement = srcRow[x];

    auto dstRow = getRow(destinationImage.devData, destinationImage.pitch, newY);
    dstRow[newX] = sourceElement;
}

ImageGPU rotateImageGPU(const ImageGPU &image, const dim3 numBlocks, const dim3 threadsPerBlock,
                        const double rotationAngle) {
    ImageGPU rotatedImage{"../rotatedImage.png"};
    const int centerX = image.width / 2, centerY = image.height / 2;

    rotatedImage.setProperties(image.height, image.width, image.channels);
    const auto radAngle = degToRad(90 + rotationAngle);

    const auto k1 = sin(radAngle);
    const auto k2 = cos(radAngle);

    rotateKernel<<<numBlocks, threadsPerBlock>>>(image, rotatedImage, k1, k2, centerX, centerY);
    CUDA_ASSERT(cudaDeviceSynchronize());

    return rotatedImage;
}

// Centralize line ////////////////////////////////////////////////////////////////////////////////////////////////////
__global__ void distanceToMarkedKernel(const ImageGPU image, unsigned *accum, unsigned *shotVal) {//NOLINT
    const int x = static_cast<int>(threadIdx.x + blockDim.x * blockIdx.x);
    const int y = static_cast<int>(threadIdx.y + blockDim.y * blockIdx.y);

    if (y >= image.height or x >= image.width) {
        return;
    }

    auto row = getRow(image.devData, image.pitch, y);
    auto element = row[x];
    if (element.isDefined and               //
        element.red == markerGPU.red and    //
        element.green == markerGPU.green and//
        element.blue == markerGPU.blue) {
        atomicAdd(accum, y);
        atomicAdd(shotVal, 1);
    }
}

__global__ void centralizeKernel(const ImageGPU sourceImage, const ImageGPU destinationImage, int offset) {//NOLINT
    const int x = static_cast<int>(threadIdx.x + blockDim.x * blockIdx.x);
    const int y = static_cast<int>(threadIdx.y + blockDim.y * blockIdx.y);

    if (y >= sourceImage.height or x >= sourceImage.width or y >= destinationImage.height or
        x >= destinationImage.width) {
        return;
    }

    auto srcRow = getRow(sourceImage.devData, sourceImage.pitch, y);
    auto dstRow = getRow(destinationImage.devData, destinationImage.pitch, y + offset);

    if (y + offset > 0 and y + offset < destinationImage.height) {
        dstRow[x] = srcRow[x];
    }
}

ImageGPU centralizeLine(const ImageGPU &image, const dim3 numBlocks, const dim3 threadsPerBlock) {
    // Do preparation calculates
    unsigned *heightAccum;
    CUDA_ASSERT(cudaMallocManaged(&heightAccum, image.width * sizeof(unsigned)))
    CUDA_ASSERT(cudaMemset(heightAccum, 0, 1))
    unsigned *shotValue;
    CUDA_ASSERT(cudaMallocManaged(&shotValue, image.width * sizeof(unsigned)))
    CUDA_ASSERT(cudaMemset(shotValue, 0, 1))

    distanceToMarkedKernel<<<numBlocks, threadsPerBlock>>>(image, heightAccum, shotValue);
    CUDA_ASSERT(cudaDeviceSynchronize())

    auto average = static_cast<int>(*heightAccum / *shotValue);
    auto shiftDistance = image.height / 2 - average;
    cout << "Shift distance: " << shiftDistance << endl;

    ImageGPU centralizedImage{"../centralized.png"};
    centralizedImage.setProperties(image.height, image.width, image.channels);

    centralizeKernel<<<numBlocks, threadsPerBlock>>>(image, centralizedImage, shiftDistance);
    CUDA_ASSERT(cudaDeviceSynchronize())
    return centralizedImage;
}

// Interpolate ////////////////////////////////////////////////////////////////////////////////////////////////////////
__global__ void interpolateKernel(const ImageGPU sourceImage, const ImageGPU destinationImage,//NOLINT
                                  const ImageGPU undefinedMap) {                              //NOLINT
    const int x = static_cast<int>(threadIdx.x + blockDim.x * blockIdx.x);
    const int y = static_cast<int>(threadIdx.y + blockDim.y * blockIdx.y);

    // Only one image can be compared, because all images have similar sizes
    if (y >= destinationImage.height or x >= destinationImage.width) {
        return;
    }

    auto srcRow = getRow(sourceImage.devData, sourceImage.pitch, y);
    if (!srcRow[x].isDefined) {
        return;
    }

    auto dstRow = getRow(destinationImage.devData, destinationImage.pitch, y);
    auto mapRow = getRow(undefinedMap.devData, undefinedMap.pitch, y);

    // rotated image cannot contain more than two undefined pixels in a row, thus we can
    if (x + 2 < sourceImage.width and !srcRow[x + 1].isDefined and !srcRow[x + 2].isDefined) {
        return;
    }

    int r{}, g{}, b{}, shots{};

    // Compare 4 pixels around
    if (x + 1 < sourceImage.width and srcRow[x + 1].isDefined) {
        r += srcRow[x + 1].red;
        g += srcRow[x + 1].green;
        b += srcRow[x + 1].blue;
        shots++;
    } else if (x - 1 >= 0 and srcRow[x - 1].isDefined) {
        r += srcRow[x - 1].red;
        g += srcRow[x - 1].green;
        b += srcRow[x - 1].blue;
        shots++;
    }
    if (y + 1 < sourceImage.height) {
        auto rowP1 = getRow(destinationImage.devData, destinationImage.pitch, y + 1);
        if (rowP1[x].isDefined) {
            r += rowP1[x].red;
            g += rowP1[x].green;
            b += rowP1[x].blue;
            shots++;
        }
    }
    if (y - 1 >= 0) {
        auto rowM1 = getRow(destinationImage.devData, destinationImage.pitch, y - 1);
        if (rowM1[x].isDefined) {
            r += rowM1[x].red;
            g += rowM1[x].green;
            b += rowM1[x].blue;
            shots++;
        }
    }
    dstRow[x] = {static_cast<uint8_t>(r / shots),//
                 static_cast<uint8_t>(g / shots),//
                 static_cast<uint8_t>(b / shots), true};
}

ImageGPU interpolateImage(const ImageGPU &image, const dim3 numBlocks, const dim3 threadsPerBlock) {

    ImageGPU interpolatedImage{"../interpolated.png"};
    interpolatedImage.setProperties(image.height, image.width, image.channels);

    ImageGPU undefinedMap{"../undefinedPixels.png"};
    undefinedMap.setProperties(image.height, image.width, image.channels);

    interpolateKernel<<<numBlocks, threadsPerBlock>>>(image, interpolatedImage, undefinedMap);
    CUDA_ASSERT(cudaDeviceSynchronize())
    return interpolatedImage;
}
// Main function //////////////////////////////////////////////////////////////////////////////////////////////////////
void rotateLine(const std::string &imagePath) {
    ImageGPU image{imagePath};
    image.readImage();

    dim3 threadsPerBlock(30, 30);// change 20 to 30
    dim3 numBlocks{(image.width + threadsPerBlock.x - 1) / threadsPerBlock.x,
                   (image.height + threadsPerBlock.y - 1) / threadsPerBlock.y};

    // Get angle to rotate the image
    const auto houghtResult = houghGPU(image, numBlocks, threadsPerBlock);
    std::cout << "Hough result: " << houghtResult << endl;
    const auto rotationAngle = houghtResult > 0 ? 90 - houghtResult : -(90 + houghtResult);
    cout << "Rotation angle: " << rotationAngle << endl;

    // Rotate the image
    auto rotatedImage = rotateImageGPU(image, numBlocks, threadsPerBlock, rotationAngle);
    rotatedImage.writeImage();

    // Shift the marked strip to the center
    auto centralizedImage = centralizeLine(rotatedImage, numBlocks, threadsPerBlock);
    centralizedImage.writeImage();
    auto interpolated = interpolateImage(centralizedImage, numBlocks, threadsPerBlock);
    interpolated.writeImage();
}

int main() {
    auto imagePath = "../images/man.png";

    cout << "GPU implementation: " << endl;
    rotateLine(imagePath);

    cout << endl << endl;
    cout << "CPU implementation: " << endl;
    runCpu(imagePath);

    return 0;
}
