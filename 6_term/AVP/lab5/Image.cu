//
// Created by sifi on 4/8/23.
//

#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

using namespace std;

Image::Image(const string &imagePath) : imageName(imagePath) {
    auto image = stbi_load(imagePath.c_str(), &width, &height, nullptr, 3);
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

Pixel Image::getPixel(int x, int y) const {
    return imageMatrix[x][y];
}

int Image::getHeight() const {
    return height;
}

int Image::getWidth() const {
    return width;
}

Image::Image() {
    imageName = "out.png";
}

bool Pixel::operator==(const Pixel &rhs) const {
    return red == rhs.red &&
           green == rhs.green &&
           blue == rhs.blue;
}

bool Pixel::operator!=(const Pixel &rhs) const {
    return !(rhs == *this);
}
