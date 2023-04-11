//
// Created by sifi on 4/8/23.
//

#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <ostream>

typedef struct Pixel {
    int red{}, green{}, blue{};

    bool operator==(const Pixel &rhs) const;

    bool operator!=(const Pixel &rhs) const;
} Pixel;

class Image {
private:
    std::string path{};
    int height{}, width{}, RGB{};
    std::string type;
    unsigned char *image;
    std::vector<std::vector<Pixel>> imageMatrix{};

public:
    explicit Image(const std::string &path);

    [[nodiscard]] int getHeight() const;

    [[nodiscard]] int getWidth() const;

    [[nodiscard]] Pixel getPixel(int x, int y) const;
};
