//
// Created by sifi on 4/8/23.
//

#pragma once

#include <fstream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

typedef struct Pixel {
    int red{}, green{}, blue{};

    bool operator==(const Pixel &rhs) const;
    bool operator!=(const Pixel &rhs) const;
} Pixel;

class Image {
private:
    std::string imagePath{};
    int height{}, width{}, channels{};
    std::vector<std::vector<Pixel>> imageMatrix{};

public:
    ~Image() = default;
    explicit Image(std::string path) : imagePath(std::move(path)){};

    // [[nodiscard]] - function return value can not be ignored and must be saved to some variable
    [[nodiscard]] int getHeight() const;
    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getChannels() const;
    void setProperties(int newHeight, int newWidth, int newChannels);

    [[nodiscard]] Pixel getPixel(int x, int y) const;
    void setPixel(int x, int y, Pixel px);

    void writeImage();
    void readImage();
};
