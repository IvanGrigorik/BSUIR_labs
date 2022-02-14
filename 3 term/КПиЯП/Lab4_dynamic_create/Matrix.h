//
// Created by Ivan on 19.09.2021.
//

#ifndef LAB4_DYNAMIC_CREATE_MATRIX_H
#define LAB4_DYNAMIC_CREATE_MATRIX_H

#include <iostream>
#include <initializer_list>

using namespace std;

class Matrix {
public:
    struct Size {
        int height{};
        int width{};
    };

private:
    int **matrix{};
    Size sizes{};

public:
    // Constructors and destructor
    explicit Matrix () = default;

    // Initialize constructor
    Matrix (initializer_list<initializer_list<int>> list_2D);

    // Copy constructor
    Matrix (const Matrix &);

    ~Matrix ();

    // Methods
    // Output in 2-nd system
    void bin_output() const;

    // Output in 8-nd system
    void oct_output () const;

    // Output in 16-nd system
    void hex_output () const;


    // Overloads

    void *operator new (size_t size);

    void *operator new[] (size_t size);

    static void operator delete (void *pointer);

    static void operator delete[] (void *pointer);

    int &operator[] (const Size &index);

    const int &operator[] (const Size &index) const;

    friend ostream &operator<< (ostream &out, const Matrix &show_matrix);

    friend Matrix operator + (const Matrix& m1, const Matrix& m2);

    // Methods
    void allocation_memory ();

    void deallocation_memory ();

    void sort_selection ();

};


#endif //LAB4_DYNAMIC_CREATE_MATRIX_H
