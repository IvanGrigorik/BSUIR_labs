#include <iostream>
#include <cmath>
#include <tuple>
#include <algorithm>
#include "Image.h"

#define degToRad(val) (val * M_PI / 180)

std::vector<std::vector<int>> houghAccum;
Pixel marker{0, 0, 0};

void houghTransform(const Image &image) {
    const int maxDist = static_cast<int>(round(sqrt(pow(image.getHeight(), 2) + pow(image.getWidth(), 2))));
    // Little theta and step optimization
    const int thetasCount = 2 * (image.getHeight() + image.getWidth()) - 4;

    // Memory allocation
    houghAccum.resize(2 * maxDist);
    for (int i = 0; i < 2 * maxDist; i++) {
        houghAccum[i].resize(thetasCount);
    }


    const int step = 180 / thetasCount >= 0 ? 1 : 180 / thetasCount;
    for (int x = 0; x < image.getWidth(); x++) {
        for (int y = 0; y < image.getHeight(); y++) {
            // Find pixel fits the marker
            if (image.getPixel(x, y) != marker) {
                continue;
            }

            // Create all possible variants of thetas

            // Iterate through all possible lines
            for (int k = -90, h = 0; k < 90; k += step, h++) {
                double idx = maxDist + x * cos(degToRad(k)) + y * sin(degToRad(k));
                houghAccum[static_cast<int>(idx)][h]++;
            }
        }
    }
}

std::tuple<int, int> findMax() {

    
    for (int i = 0; i < houghAccum.size(); i++){

    }

    return std::make_tuple<>(1, 2);
}

int main() {
    using namespace std;
    Image image{"../images/straight_line.png"};
    cout << "Image height: " << image.getHeight() << endl << "Image width: " << image.getWidth() << endl;

    houghTransform(image);

    cout << endl << "Hough result: " << endl;

    for (auto &i: houghAccum) {
        for (auto j: i) {
            cout << j << ' ';
        }
        cout << endl;
    }

    return 0;
}
