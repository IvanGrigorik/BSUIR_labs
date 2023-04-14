#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include "Image.h"

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
    for (int i = 0; i < 2 * maxDist; i++) {
        houghAccum[i].resize(thetasCount);
    }

    const float step = 180.f / static_cast<float>(thetasCount);
    std::vector<float> thetas;


    for (int x = 0; x < image.getHeight(); x++) {
        for (int y = 0; y < image.getWidth(); y++) {
            // Find pixel fits the marker
            if (image.getPixel(x, y) != marker) {
                continue;
            }

            // Iterate through all possible lines (need to rewrite)
            double ang = -90;
            for (int h = 0; h < thetasCount; ang += step, h++) {
                int idx = static_cast <int>(maxDist + x * cos(degToRad(ang)) + y * sin(degToRad(ang)));
                houghAccum[idx][h]++;
            }
        }
    }

    ulong idx{}, max{};
    for (auto &i: houghAccum) {
        for (int j = 0; j < i.size(); j++) {
            if (i[j] > max) {
                max = i[j];
                idx = j;
            }
        }
    }

    double angle{-90};
    for (int i = 0; i < idx; i++) {
        angle += step;
    }
    return static_cast<int>(angle);
}


int main() {
    using namespace std;
    Image image{"../images/line65.png"};
    cout << "Image height: " << image.getHeight() << endl << "Image width: " << image.getWidth() << endl;

    //
    auto angle = houghTransform(image);



    cout << endl << "Hough result: " << angle << endl;

    return 0;
}
