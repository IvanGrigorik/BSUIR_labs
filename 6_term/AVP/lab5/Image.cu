//
// Created by sifi on 4/8/23.
//

#include "Image.cuh"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

using namespace std;

void Image::readImage() {
    auto image = stbi_load(imagePath.c_str(), &width, &height, &channels, 3);
    if (height == 0) {
        perror("Image opening failed");
        exit(-1);
    }

    imageMatrix.resize(height);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // In format RGB (+0 - R; +1 - G; +2 - B)
            imageMatrix[i].push_back({image[(i * width + j) * 3],
                                      image[(i * width + j) * 3 + 1],
                                      image[(i * width + j) * 3 + 2]});
        }
    }
}

void Image::writeImage() {
    auto *image = new unsigned char[height * width * channels];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[(i * width + j) * 3] = imageMatrix[i][j].red;
            image[(i * width + j) * 3 + 1] = imageMatrix[i][j].green;
            image[(i * width + j) * 3 + 2] = imageMatrix[i][j].blue;
        }
    }

    stbi_write_png(imagePath.c_str(), width, height, channels, image, width * channels);
}

Pixel Image::getPixel(int x, int y) const {
    return imageMatrix[x][y];
}

void Image::setPixel(int x, int y, Pixel px) {
    imageMatrix[x][y] = px;
}

int Image::getHeight() const {
    return height;
}

int Image::getWidth() const {
    return width;
}

int Image::getChannels() const {
    return channels;
}

void Image::setProperties(int newHeight, int newWidth, int newChannels) {
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

bool Pixel::operator==(const Pixel &rhs) const {
    return red == rhs.red &&
           green == rhs.green &&
           blue == rhs.blue;
}

bool Pixel::operator!=(const Pixel &rhs) const {
    return !(rhs == *this);
}
