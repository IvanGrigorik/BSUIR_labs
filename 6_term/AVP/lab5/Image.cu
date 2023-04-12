//
// Created by sifi on 4/8/23.
//

#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION

#include "libs/stb_image.h"

using namespace std;

Image::Image(const string &imagePath) : path(imagePath) {

    int originalNoChannel;
    int desiredChannels = 3;
    image = stbi_load(imagePath.c_str(), &height, &width, &originalNoChannel, desiredChannels);
    if (height == 0) {
        perror("Image opening failed");
        exit(-1);
    }

    imageMatrix.resize(height);
    for (int i = 0; i < height; ++i) {
        imageMatrix[i].resize(width);
    }

    int r, g, b;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            r = image[(i * width + j) * 3];
            g = image[(i * width + j) * 3 + 1];
            b = image[(i * width + j) * 3 + 2];
            imageMatrix[i][j] = {r, g, b};
        }
    }
    stbi_image_free(image);
}

Pixel Image::getPixel(int x, int y) const {
    return imageMatrix[x][y];
}

int Image::getHeight() const {
    return height;
}

int Image::getWidth() const {
    return width;
}

bool Pixel::operator==(const Pixel &rhs) const {
    return red == rhs.red &&
           green == rhs.green &&
           blue == rhs.blue;
}

bool Pixel::operator!=(const Pixel &rhs) const {
    return !(rhs == *this);
}
