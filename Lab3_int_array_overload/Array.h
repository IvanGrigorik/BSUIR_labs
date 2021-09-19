//
// Created by Ivan on 08.09.2021.
//

#ifndef LAB3_INT_ARRAY_OVERLOAD_ARRAY_H
#define LAB3_INT_ARRAY_OVERLOAD_ARRAY_H

#include "Array_size.h"

#include <initializer_list>

using namespace std;

class Array {
private:
    int *arr{};
    int arr_size{};
    static const int ARR_SIZE = 100;
public:

    // Constructor and destructor
    Array ();
    Array (Array const &);

    ~Array ();

    // Overloaded operators

    // Initialize
    void operator() (const initializer_list<int> &new_arr);

    // Indexing
    // Get array index
    int &operator[] (int index);

    // Increase all digits by 1
    Array operator++ (int);
    Array &operator++ ();

    // Compare two arrays
    // P. S. If the sizes are different, return true/false
    bool operator< (const Array &arr_to_comparison) const;

    // Adds another of the same size to one array
    Array operator+ (const Array &arr_to_add) const;

    // Assigning arrays
    Array &operator= (Array const &);


    // Friend overloaded operators

    // Decrease all digits by 1
    friend Array operator-- (Array &arr_to_subtract);
    friend Array operator-- (Array &arr_to_subtract, int);

    // Add one array to another
    // P. S. array should have same size
    friend Array operator+ (Array &arr_to_add_number, int number);

    // Compare power of the array with int number
    friend bool operator> (const Array &arr_to_compare, int number);

    // Overloaded array output
    friend ostream &operator<< (ostream &out, Array &arr_to_show);


    // Overloaded conversion operators

    // Return average value in array
    explicit operator double ();

    // Convert to array size
    explicit operator Array_size() const;
};


#endif //LAB3_INT_ARRAY_OVERLOAD_ARRAY_H
