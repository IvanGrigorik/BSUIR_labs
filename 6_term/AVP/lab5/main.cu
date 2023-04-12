#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include "Image.h"

#define degToRad(val) (val * M_PI / 180)
#define radToDeg(val) (val * 180 / M_PI)

std::vector<std::vector<int>> houghAccum;
Pixel marker{0, 0, 0};

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

    double angelBotBorder = -90;
    while (angelBotBorder < 90) {
        angelBotBorder += step;
        thetas.push_back(degToRad(angelBotBorder));
    }

    for (int x = 0; x < image.getWidth(); x++) {
        for (int y = 0; y < image.getHeight(); y++) {
            // Find pixel fits the marker
            if (image.getPixel(x, y) != marker) {
                continue;
            }

            // Iterate through all possible lines (need to rewrite)
            for (int h = 0; h < thetasCount; h++) {
                double idx = maxDist + x * cos(thetas[h]) + y * sin(thetas[h]);
                houghAccum[static_cast<int>(idx)][static_cast<int>(h)]++;
            }
        }
    }

    ulong idx{}, max{};
    for (int i = 0; i < houghAccum.size(); i++) {
        for (int j = 0; j < houghAccum[i].size(); j++) {
            if (houghAccum[i][j] > max) {
                max = houghAccum[i][j];
                idx = i * houghAccum.size() + j;
            }
        }
    }

    auto angle = thetas[static_cast<int>(idx % thetasCount)];
    return radToDeg(angle);
}


int main() {
    using namespace std;
    Image image{"../images/line65.png"};
    cout << "Image height: " << image.getHeight() << endl << "Image width: " << image.getWidth() << endl;

    auto angle = houghTransform(image);

    cout << endl << "Hough result: " << angle << endl;

//    for (auto &i: houghAccum) {
//        for (auto j: i) {
//            cout << setw(2) << j << ' ';
//        }
//        cout << endl;
//    }

    return 0;
}
