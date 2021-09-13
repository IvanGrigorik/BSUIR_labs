//
// Created by Ivan on 08.09.2021.
//

#ifndef LAB3_INT_ARRAY_OVERLOAD_ARRAY_H
#define LAB3_INT_ARRAY_OVERLOAD_ARRAY_H

#include <fstream>
#include <iostream>
#include <cassert>
#include <initializer_list>

using namespace std;

const int ARR_SIZE = 100;

class Array {
private:
    int *arr{};
    int arr_size{};
public:
    Array ();

    ~Array ();

    void operator() (const initializer_list<int> &new_arr);

    int &operator[] (int index);

    //Array operator= (Array arr_to_copy);

    // for postfix form (remember to add 1 to all numbers in array with postfix form, not to use this "int")
    int *operator++ (int);

    bool operator< (const Array& arr_to_comparison) const;

    Array operator+ (const Array& arr_to_add) const;

    Array &operator= (Array const& );


    friend Array operator-- (Array &arr_to_subtract);

    friend Array operator+ (Array &arr_to_add_number, int number);

    friend bool operator< (const Array& arr_to_compare, int number);

    friend ostream &operator<< (ostream &out, Array& arr_to_show);
};


#endif //LAB3_INT_ARRAY_OVERLOAD_ARRAY_H
