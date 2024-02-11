#ifndef MATRIX_HPP
#define MATRIX_HPP

class Matrix {
private:
    int** matrix;
    int X;
    int Y;

public:

    // Constructor and destructors
    Matrix(int n, int m);
    ~Matrix();

    // Functions
    void PrintMatrix() const;
    void Randomize();
    Matrix multiply();

    // Overloaded operators
    int* operator[](int i) const { return *(matrix + i); }
    int*& operator[](int i) { return matrix[i]; }
};

#endif
