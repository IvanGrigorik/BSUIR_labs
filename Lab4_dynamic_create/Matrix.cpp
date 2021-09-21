//
// Created by Ivan on 19.09.2021.
//

#include "Matrix.h"
#include <cassert>

// Constructors and destructor
Matrix::Matrix (initializer_list<initializer_list<int>> list_2D) {

    sizes.height = static_cast<int>(list_2D.size());
    sizes.width = static_cast<int>(list_2D.begin()->size());

    // Check for equal with of every array
    for (auto &list_1D: list_2D)
        assert(list_1D.size() == sizes.width);

    allocation_memory();

    int i = 0;
    int j;

    for (auto &list_1D: list_2D) {
        j = 0;
        for (auto &element: list_1D) {
            matrix[i][j] = element;
            j++;
        }
        i++;
    }
    cout << "Initialize work" << endl;
}

Matrix::Matrix (const Matrix &matrix_to_copy) {
    sizes = matrix_to_copy.sizes;

    allocation_memory();

    for (int i = 0; i < sizes.height; i++)
        for (int j = 0; j < sizes.width; j++)
            matrix[i][j] = matrix_to_copy.matrix[i][j];
}

Matrix::~Matrix () {
    cout << "Deallocation work" << endl;
    deallocation_memory();
}

// Overloads
void *Matrix::operator new (size_t size) {
    cout << "New work" << endl;
    void *pointer = ::operator new(size);
    return pointer;
}

void *Matrix::operator new[] (size_t size) {
    cout << "New[] work" << endl;
    void *pointer = ::operator new[](size);
    return pointer;
}

void Matrix::operator delete (void *pointer) {
    cout << "Delete work" << endl;
    ::operator delete(pointer);
}

void Matrix::operator delete[] (void *pointer) {
    cout << "Delete work" << endl;
    ::operator delete[](pointer);
}

int &Matrix::operator[] (const Matrix::Size &index) {
    return matrix[index.height][index.width];
}

const int &Matrix::operator[] (const Matrix::Size &index) const {
    return matrix[index.height][index.width];
}

ostream &operator<< (ostream &out, const Matrix &show_matrix) {
    for (int i = 0; i < show_matrix.sizes.height; i++) {
        for (int j = 0; j < show_matrix.sizes.width; j++)
            out << show_matrix.matrix[i][j] << ' ';
        out << endl;
    }
    return out;
}

// Methods

// Matrix sort
void Matrix::sort_selection () {
    for (int i = 0; i < sizes.height; ++i) {
        for (int j = 0; j < sizes.width; ++j) {
            int &current = matrix[i][j];
            int *min = &current;

            Size index{i, j + 1};

            while (index.height < sizes.height) {
                while (index.width < sizes.width) {
                    if ((*this)[index] < *min)
                        min = &(*this)[index];
                    index.width++;
                }
                index.width = 0;
                index.height++;
            }
            swap(current, *min);
        }
    }
}

// Allocation memory for matrix
void Matrix::allocation_memory () {
    matrix = new int *[sizes.height];

    for (int i = 0; i < sizes.height; ++i) {
        matrix[i] = new int[sizes.width];

        for (int j = 0; j < sizes.width; ++j)
            matrix[i][j] = 0;
    }
}

// Deallocate
void Matrix::deallocation_memory () {
    for (int i = 0; i < sizes.height; ++i)
        delete[] matrix[i];
    delete[] matrix;
}
