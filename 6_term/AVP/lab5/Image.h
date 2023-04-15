//
// Created by sifi on 4/8/23.
//

#pragma once

#include <fstream>
#include <ostream>
#include <string>
#include <vector>

typedef struct Pixel {
    int red{}, green{}, blue{};

    bool operator==(const Pixel &rhs) const;

    bool operator!=(const Pixel &rhs) const;
} Pixel;

class Image {
private:
    std::string imageName{};
    int height{}, width{};
    std::vector<std::vector<Pixel>> imageMatrix{};

public:
    Image();

    explicit Image(const std::string &path);

    // [[nodiscard]] - function return value can not be ignored and must be saved to some variable
    [[nodiscard]] int getHeight() const;

    [[nodiscard]] int getWidth() const;

    [[nodiscard]] Pixel getPixel(int x, int y) const;

};
