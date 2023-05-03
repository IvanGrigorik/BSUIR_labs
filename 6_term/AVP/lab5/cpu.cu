#include "cpu.cuh"
#include <iostream>
#include <utility>

std::vector<std::vector<int>> houghAccum;
Pixel thresholdCPU{20, 20, 20};
Pixel markerCPU{0, 255, 0};

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
double houghTransform(const ImageCPU &image) {
    ImageCPU monochromaticImage{"../outImages/monochromatic.png"};
    monochromaticImage.setProperties(image.getHeight(), image.getWidth(), image.getChannels());
    const int maxDist = static_cast<int>(round(sqrt(pow(image.getHeight(), 2) + pow(image.getWidth(), 2))));
    // Little theta and step optimization
    const int thetasCount = 2 * (image.getHeight() + image.getWidth()) - 4;

    // Memory allocation
    houghAccum.resize(2 * maxDist);
    for (int i = 0; i < 2 * maxDist; i++) {
        houghAccum[i].resize(thetasCount);
    }

    const float step = 180.f / static_cast<float>(thetasCount);

    for (int y = 0; y < image.getHeight(); y++) {
        for (int x = 0; x < image.getWidth(); x++) {
            // Find pixel fits the markerCPU

            if (abs(image.getPixel(x, y).red - markerCPU.red) >= thresholdCPU.red or      //
                abs(image.getPixel(x, y).green - markerCPU.green) >= thresholdCPU.green or//
                abs(image.getPixel(x, y).blue - markerCPU.blue) >= thresholdCPU.blue) {
                continue;
            }
            monochromaticImage.setPixel(x, y, {255, 255, 255});
            double ang = -90;
            for (int h = 0; h < thetasCount; ang += step, h++) {
                int idx = static_cast<int>(maxDist + x * cos(degToRad(ang)) + y * sin(degToRad(ang)));
                houghAccum[idx][h]++;
            }
        }
    }


    monochromaticImage.writeImage();
    int idx{}, max{};
    for (auto &i: houghAccum) {
        for (int j = 0; j < i.size(); j++) {
            if (i[j] > max) {
                max = i[j];
                idx = j;
            }
        }
    }


    return -90 + step * static_cast<float>(idx);
}

ImageCPU rotateImage(const ImageCPU &image, const double angle) {
    ImageCPU rotatedImage{"../outImages/rotatedImage.png"};

    const auto height = image.getHeight(), width = image.getWidth();

    const int centerX = width / 2, centerY = height / 2;
    rotatedImage.setProperties(height, width, image.getChannels());

    const auto radAngle = degToRad(90 + angle);

    const auto k1 = sin(radAngle);
    const auto k2 = cos(radAngle);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            auto newX = static_cast<int>(k1 * (x - centerX) + k2 * (y - centerY) + centerX);
            auto newY = static_cast<int>(k1 * (y - centerY) - k2 * (x - centerX) + centerY);

            if (newX < 0 or newX >= width or newY < 0 or newY >= height) {
                continue;
            }

            rotatedImage.setPixel(newX, newY, image.getPixel(x, y));
            rotatedImage.definePixel(newX, newY);
        }
    }

    rotatedImage.writeImage();
    return rotatedImage;
}

ImageCPU interpolarImage(const ImageCPU &image) {
    ImageCPU interpolaredImage{image};
    auto height = image.getHeight(), width = image.getWidth();
    ImageCPU undefinedMap{"../outImages/undefinedPixels.png"};
    undefinedMap.setProperties(height, width, image.getChannels());

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (!interpolaredImage.getPixel(x, y).isDefined) {
                Pixel newPixel{};

                // rotated image cannot contain more than two undefined pixels in a row
                if (x + 2 < width and !image.getPixel(x + 1, y).isDefined and !image.getPixel(x + 2, y).isDefined) {
                    continue;
                }

                int shots{};
                if (x + 1 < width and image.getPixel(x + 1, y).isDefined) {
                    newPixel = image.getPixel(x + 1, y);
                    shots++;
                }
                if (x - 1 >= 0 and image.getPixel(x - 1, y).isDefined) {
                    newPixel += image.getPixel(x - 1, y);
                    shots++;
                }
                if (y + 1 < height and image.getPixel(x, y + 1).isDefined) {
                    newPixel += image.getPixel(x, y + 1);
                    shots++;
                }
                if (y - 1 >= 0 and image.getPixel(x, y - 1).isDefined) {
                    newPixel += image.getPixel(x, y - 1);
                    shots++;
                }
                if (shots != 0) {
                    newPixel.red /= shots;
                    newPixel.green /= shots;
                    newPixel.blue /= shots;
                    newPixel.isDefined = true;
                }
                interpolaredImage.setPixel(x, y, newPixel);
                undefinedMap.setPixel(x, y, {255, 255, 255});
            }
        }
    }

    undefinedMap.writeImage();
    return interpolaredImage;
}

int distanceToMarkedLine(const ImageCPU &image) {
    int length{}, shots{};

    for (int i = 0; i < image.getHeight(); i++) {
        for (int j = 0; j < image.getWidth(); j++) {
            if (image.getPixel(j, i) == markerCPU) {
                length += i;
                shots++;
            }
        }
    }

    return length / shots;
}

ImageCPU centralizeLine(const ImageCPU &image, int offset) {
    ImageCPU centralizedImage{"../outImages/centralized.png"};
    auto height = image.getHeight(), width = image.getWidth();
    centralizedImage.setProperties(height, width, image.getChannels());

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (y + offset > 0 and y + offset < height) {
                Pixel px = image.getPixel(x, y);
                centralizedImage.setPixel(x, y + offset, px);
                if (px.isDefined) {
                    centralizedImage.definePixel(x, y + offset);
                }
            }
        }
    }

    centralizedImage.writeImage();
    return centralizedImage;
}

void runCpu(std::string imagePath) {
    using namespace std;

    cout << "CPU running" << endl;
    ImageCPU image{std::move(imagePath)};
    image.readImage();
    cout << "ImageCPU height: " << image.getHeight() << endl << "ImageCPU width: " << image.getWidth() << endl;

    // Get angle to rotate image
    const auto houghtResult = houghTransform(image);
    cout << endl << "Hough result: " << houghtResult << endl;
    const auto rotationAngle = houghtResult > 0 ? 90 - houghtResult : -(90 + houghtResult);
    cout << "Rotation angle: " << rotationAngle << endl;

    // Rotate image
    auto outImage = rotateImage(image, rotationAngle);

    // Get shift distance to centralize line
    auto shiftDistance = outImage.getHeight() / 2 - distanceToMarkedLine(outImage);
    cout << "Shift distance: " << shiftDistance << endl;

    // Centralize line
    outImage = centralizeLine(outImage, shiftDistance);

    // Interpolate the image
    outImage = interpolarImage(outImage);
    outImage.setImageName("../outImages/outImage.png");
    outImage.writeImage();
}