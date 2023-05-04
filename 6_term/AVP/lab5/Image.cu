//
// Created by sifi on 4/8/23.
//

#include "Image.cuh"
#include "utilities.cuh"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

using namespace std;
#include <iostream>

void ImageCPU::readImage() {
    auto image = stbi_load(imageName.c_str(), &width, &height, &channels, 3);
    if (height == 0) {
        perror("ImageCPU opening failed");
        exit(-1);
    }

    imageMatrix.resize(height);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // In format RGB (+0 - R; +1 - G; +2 - B)
            imageMatrix[i].push_back(
                    {image[(i * width + j) * 3], image[(i * width + j) * 3 + 1], image[(i * width + j) * 3 + 2]});
        }
    }
}

void ImageCPU::writeImage() const {
    auto *image = new unsigned char[height * width * channels];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[(i * width + j) * 3] = imageMatrix[i][j].red;
            image[(i * width + j) * 3 + 1] = imageMatrix[i][j].green;
            image[(i * width + j) * 3 + 2] = imageMatrix[i][j].blue;
        }
    }

    stbi_write_png(imageName.c_str(), width, height, channels, image, width * channels);
}

Pixel ImageCPU::getPixel(int x, int y) const {
    return imageMatrix[y][x];
}

void ImageCPU::setPixel(int x, int y, const Pixel px) {
    imageMatrix[y][x] = px;
}

void ImageCPU::definePixel(int x, int y) {
    imageMatrix[y][x].isDefined = true;
}

int ImageCPU::getHeight() const {
    return height;
}

int ImageCPU::getWidth() const {
    return width;
}

int ImageCPU::getChannels() const {
    return channels;
}

void ImageCPU::setProperties(int newHeight, int newWidth, int newChannels) {
    height = newHeight;
    width = newWidth;
    channels = newChannels;

    if (!imageMatrix.empty()) {
        imageMatrix.clear();
    }

    imageMatrix.resize(height);
    for (int i = 0; i < height; i++) {
        imageMatrix[i].resize(width);
    }
}

void ImageCPU::setImageName(const string &name) {
    ImageCPU::imageName = name;
}

bool Pixel::operator==(const Pixel &rhs) const {
    return red == rhs.red && green == rhs.green && blue == rhs.blue;
}

bool Pixel::operator!=(const Pixel &rhs) const {
    return !(rhs == *this);
}

Pixel &Pixel::operator+=(const Pixel &rhs) {
    red += rhs.red;
    green += rhs.green;
    blue += rhs.blue;

    return *this;
}

// ImageGPU implementation
void ImageGPU::readImage() {
    auto image = stbi_load(imagePath.c_str(), &width, &height, &channels, 3);
    if (height == 0) {
        perror("ImageCPU opening failed");
        exit(-1);
    }

    auto imageMatrix = new GPUPixel[height * width];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // In format RGB (+0 - R; +1 - G; +2 - B)
            imageMatrix[i * width + j] = {image[(i * width + j) * 3], image[(i * width + j) * 3 + 1],
                                          image[(i * width + j) * 3 + 2], true};
        }
    }

    // Malloc pitched memory for kernels
    CUDA_ASSERT(cudaMallocPitch(&devData, &pitch, width * sizeof(GPUPixel), height))
    CUDA_ASSERT(cudaMemcpy2D(devData, pitch, imageMatrix, width * sizeof(GPUPixel), width * sizeof(GPUPixel), height,
                             cudaMemcpyHostToDevice))
}
void ImageGPU::setProperties(int newHeight, int newWidth, int newChannels) {
    height = newHeight;
    width = newWidth;
    channels = newChannels;

    if (pitch != 0) {
        CUDA_ASSERT(cudaFree(&devData));
    }
    auto imageMatrix = new GPUPixel[height * width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // In format RGB (+0 - R; +1 - G; +2 - B), plus "is defined" variable
            imageMatrix[i * width + j] = {0, 0, 0, false};
        }
    }
    CUDA_ASSERT(cudaMallocPitch(&devData, &pitch, width * sizeof(GPUPixel), height))
    CUDA_ASSERT(cudaMemcpy2D(devData, pitch, imageMatrix, width * sizeof(GPUPixel), width * sizeof(GPUPixel), height,
                             cudaMemcpyHostToDevice))
}
void ImageGPU::writeImage() const {
    auto imageMatrix = new GPUPixel[height * width];

    CUDA_ASSERT(cudaMemcpy2D(imageMatrix, width * sizeof(GPUPixel),//
                             devData, pitch,                       //
                             width * sizeof(GPUPixel), height,     //
                             cudaMemcpyDeviceToHost))

    auto *image = new unsigned char[height * width * channels];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[(i * width + j) * 3] = imageMatrix[i * width + j].red;
            image[(i * width + j) * 3 + 1] = imageMatrix[i * width + j].green;
            image[(i * width + j) * 3 + 2] = imageMatrix[i * width + j].blue;
        }
    }

    stbi_write_png(imagePath.c_str(), width, height, channels, image, width * channels);
}
