#include "Image.cuh"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>

#define degToRad(val) (val * M_PI / 180)

std::vector<std::vector<int>> houghAccum;
Pixel marker{0, 0, 0};

/// Returns line angle relative to the horizon (see explanation ahead the function)
/*
 * |                     ----
 * |                 ----
 * |             ---- A (equivalent)
 * | ****************************** horizon line
 * |       A ----
 * |     ----
 * | ----
 * |||||||||||||||||||||||||||||||| image x-axis
 * Return angle A
 */
int houghTransform(const Image &image) {
    const int maxDist = static_cast<int>(round(sqrt(pow(image.getHeight(), 2) + pow(image.getWidth(), 2))));
    // Little theta and step optimization
    const int thetasCount = 2 * (image.getHeight() + image.getWidth()) - 4;

    // Memory allocation
    houghAccum.resize(2 * maxDist);
    for (int i = 0; i < 2 * maxDist; i++) { houghAccum[i].resize(thetasCount); }

    const float step = 180.f / static_cast<float>(thetasCount);

    for (int x = 0; x < image.getHeight(); x++) {
        for (int y = 0; y < image.getWidth(); y++) {
            // Find pixel fits the marker
            if (image.getPixel(x, y) != marker) { continue; }

            double ang = -90;
            for (int h = 0; h < thetasCount; ang += step, h++) {
                int idx = static_cast<int>(maxDist + x * cos(degToRad(ang)) + y * sin(degToRad(ang)));
                houghAccum[idx][h]++;
            }
        }
    }

    int idx{}, max{};
    for (auto &i: houghAccum) {
        for (int j = 0; j < i.size(); j++) {
            if (i[j] > max) {
                max = i[j];
                idx = j;
            }
        }
    }

    return static_cast<int>(-90 + step * static_cast<float>(idx));
}

Image rotateImage(const Image &image, const int angle) {
    Image newImage{"../outImage.png"};
    const int maxDist = static_cast<int>(round(sqrt(pow(image.getHeight(), 2) + pow(image.getWidth(), 2))));
    auto centerX = image.getWidth() / 2, centerY = image.getHeight() / 2;
    newImage.setProperties(maxDist, maxDist, image.getChannels());

    auto angCos = cos(degToRad(angle)), angSin = sin(degToRad(angle));
    for (int i = 0; i < image.getHeight(); i++) {
        for (int j = 0; j < image.getWidth(); j++) {
            auto x = static_cast<int>((i - centerX) * angCos + (j - centerY) * angSin);
            auto y = static_cast<int>((j - centerY) * angCos - (i - centerX) * angSin);

//            if (x > maxDist or x < 0 or y > maxDist or y < 0) { continue; }

            newImage.setPixel(x, y, image.getPixel(i, j));
        }
    }

    newImage.writeImage();
}

int main() {
    using namespace std;
    Image image{"../images/straight_line.png"};
    image.readImage();
    cout << "Image height: " << image.getHeight() << endl << "Image width: " << image.getWidth() << endl;

    // Get angle to rotate image
    const auto rotationAngle = houghTransform(image);
    cout << endl << "Hough result: " << rotationAngle << endl;


    Image rotatedImage = rotateImage(image, rotationAngle);

    return 0;
}
