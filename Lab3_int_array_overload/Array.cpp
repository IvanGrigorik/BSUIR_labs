//
// Created by Ivan on 08.09.2021.
//

#include "Array.h"

#include <iostream>
#include <cassert>

// Some constructors
Array::Array () {
}

Array::Array (const Array &arr1) {
    delete [] arr;
    arr = new int [arr1.arr_size];
    arr_size = arr1.arr_size;
    for(int i = 0; i < arr_size; i++)
        arr[i] = arr1.arr[i];
}

Array::~Array () {
    delete[] arr;
}

// Some methods
void Array::operator() (const initializer_list<int> &list) {
    arr_size = static_cast<int>(list.size());
    arr = new int[arr_size];

    int i = 0;
    for (auto element: list) {
        arr[arr_size - list.size() + i] = element;
        i++;
    }
    cout << endl;
}

int &Array::operator[] (int index) {
    assert(index < ARR_SIZE && "Invalid array index!");
    return arr[index];
}

// Operator to subtract one from every number in array
Array &operator-- (Array &arr_to_subtract) {
    assert(arr_to_subtract.arr_size > 0 && "Invalid array index!");
    for (int i = 0; i < arr_to_subtract.arr_size; i++) {
        arr_to_subtract[i]--;
    }
    return arr_to_subtract;
}

Array &operator-- (Array &arr_to_subtract, int) {
    assert(arr_to_subtract.arr_size > 0 && "Invalid array index!");
    Array *arr_before_subtracting = new Array(arr_to_subtract);
    --arr_to_subtract;
    return *arr_before_subtracting;
}

// Operator to add number to every number from the array
Array operator+ (Array &arr_to_add_number, int number) {
    for (int i = 0; i < arr_to_add_number.arr_size; i++) {
        arr_to_add_number[i] += number;
    }
    return arr_to_add_number;
}

// In my opinion, that func should compare power (size) of array with number (which should be also power of array)
bool operator> (const Array &arr_to_compare, int number) {
    return arr_to_compare.arr_size > number;
}

// Operator to show array
ostream &operator<< (ostream &out, Array &arr_to_show) {
    for (int i = 0; i < arr_to_show.arr_size; i++) {
        if (i == arr_to_show.arr_size - 1) {
            out << arr_to_show[i];
            break;
        }
        out << arr_to_show[i] << " ";
    }
    return out;
}

// Prefix form
Array &Array::operator++ () {
    assert((*this).arr_size > 0 && "Invalid array index!");
    for (int i = 0; i < arr_size; i++) {
        arr[i]++;
    }
    return *this;
}

//Postfix form
Array &Array::operator++ (int) {
    assert((*this).arr_size > 0 && "Invalid array index!");
    Array *arr_before_incrementing = new Array(*this);
    ++(*this);
    return *arr_before_incrementing;
}

// In my opinion, that func should compare one array with another, and if power of arrays
// are not same - they should return false

// Realization is shitty
bool Array::operator< (const Array &arr_to_comparison) const {
    if (arr_size < arr_to_comparison.arr_size)
        return false;
    else if (arr_size > arr_to_comparison.arr_size)
        return true;

    bool is_more = false;
    for (int i = 0; i < arr_size; i++) {
        if (arr[i] < arr_to_comparison.arr[i])
            is_more = true;
        else
            is_more = false;
    }
    return is_more;
}

Array Array::operator+ (const Array &arr_to_add) const {
    assert(arr_size == arr_to_add.arr_size && "Invalid input!");

    auto *temp = new Array[arr_size];
    temp->arr = arr;
    temp->arr_size = arr_size;

    for (int i = 0; i < arr_size; i++) {
        temp->arr[i] += arr_to_add.arr[i];
    }
    return *temp;
}

Array &Array::operator= (Array const &arr_to_add) {
    if (this == &arr_to_add)
        return *this;

    delete[] arr;
    arr_size = arr_to_add.arr_size;
    arr = new int[arr_size];
    for (int i = 0; i < arr_size; i++)
        arr[i] = arr_to_add.arr[i];
    return *this;
}

Array::operator double () {
    double average_value = 0;

    for (int i = 0; i < arr_size; i++) {
        average_value += arr[i];
    }
    average_value /= arr_size;
    return average_value;
}

Array::operator Array_size () const {
    Array_size size{arr_size};
    return size;
}


Array &Array::operator- (const Array &arr2) {
    --(*this);
    assert(arr_size == arr2.arr_size && "Invalid array's size");

    Array *array = new Array{(*this)};
    for(int i = 0; i < arr_size; i++){
        array->arr[i] = arr[i] / arr2.arr[i];
    }
    return *array;
}
