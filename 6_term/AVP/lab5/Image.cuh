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
    bool isDefined = false;
    bool operator==(const Pixel &rhs) const;
    bool operator!=(const Pixel &rhs) const;
    Pixel &operator+=(const Pixel &rhs);
} Pixel;

class Image {
private:
    std::string imageName{};
    int height{}, width{}, channels{};
    std::vector<std::vector<Pixel>> imageMatrix{};

public:
    [[maybe_unused]] explicit Image(std::string path) : imageName(std::move(path)){};

    // [[nodiscard]] - function return value can not be ignored and must be saved to some variable
    [[nodiscard]] int getHeight() const;
    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getChannels() const;
    void setImageName(const std::string &name);
    void setProperties(int newHeight, int newWidth, int newChannels);

    [[nodiscard]] Pixel getPixel(int x, int y) const;
    void setPixel(int x, int y, Pixel px);
    void definePixel(int x, int y);

    void writeImage() const;
    void readImage();
};
