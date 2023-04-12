#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
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

    const float step = 180.f / static_cast<float>(thetasCount);
    std::vector<float> thetas;
    thetas.resize(thetasCount);

    double ang = -90;
    while (ang < 90) {
        ang += step;
        thetas.push_back(degToRad(ang));
    }

    for (int x = 0; x < image.getWidth(); x++) {
        for (int y = 0; y < image.getHeight(); y++) {
            // Find pixel fits the marker
            if (image.getPixel(x, y) != marker) {
                continue;
            }



            // Iterate through all possible lines (need to rewrite)
            for (double k = -90, h = 0; k < 90; k += step, h++) {
                double idx = x * cos(degToRad(k)) + y * sin(degToRad(k));
                houghAccum[static_cast<int>(idx) + maxDist][static_cast<int>(h)]++;
            }
        }
    }


}


int main() {
    using namespace std;
    Image image{"../images/line3x3.png"};
    cout << "Image height: " << image.getHeight() << endl << "Image width: " << image.getWidth() << endl;

    houghTransform(image);

    cout << endl << "Hough result: " << endl;

    for (auto &i: houghAccum) {
        for (auto j: i) {
            cout << setw(2) << j << ' ';
        }
        cout << endl;
    }

    return 0;
}
