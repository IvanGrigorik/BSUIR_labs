#include "Matrix.hpp"

#include <iostream>
#include <random>

Matrix::Matrix(int n, int m)
    : X(n)
    , Y(m)
{
    // Allocate memory for matrix
    this->matrix = new int*[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[m];
    }
}

void Matrix::Randomize()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> distrib(1, 255);

    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            matrix[i][j] = distrib(gen);
        }
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < X; ++i) {
        delete[] this->matrix[i];
    }
    delete[] this->matrix;
}

void Matrix::PrintMatrix() const
{
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            std::cout << matrix[i][j] << "\t"; // print the result
        }
        std::cout << '\n';
    }
}
