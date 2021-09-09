//
// Created by Ivan on 08.09.2021.
//

#include "Array.h"

// Some constructors
Array::Array () {
    arr_size = 0;
}

Array::~Array () {
    --arr_size;
}

// Some methods

void Array::operator() (const initializer_list<int> &list) {

//    // Reallocation memory (bad way)
//    int *arr_temp = arr;
//    arr = new int[temp_size];
//    arr = arr_temp;

    arr_size += static_cast<int>(list.size());
    arr = new int[arr_size];

    int i = 0;
    for (auto element : list) {
        arr[arr_size - list.size() + i] = element;
        i++;
    }
    cout << endl;
}

int &Array::operator[] (int index) {
    assert(index < ARR_SIZE && "Invalid array index!");
    return arr[index];
}

// Operator to subtract last number from our array
Array operator-- (Array &arr_to_subtract) {
    assert(arr_to_subtract.arr_size > 0 && "Invalid array index!");
    --arr_to_subtract.arr_size;
    arr_to_subtract.arr = (int *)realloc(arr_to_subtract.arr, arr_to_subtract.arr_size);
    return arr_to_subtract;
}

// Operator to add new number to array
Array operator+ (Array &arr_to_add_number, int number) {
    // Reallocation memory
    arr_to_add_number.arr_size += 1;
    arr_to_add_number.arr = (int *) realloc(arr_to_add_number.arr, arr_to_add_number.arr_size);

    // Add number to next address
    arr_to_add_number[arr_to_add_number.arr_size - 1] = number;
    return arr_to_add_number;
}

// In my opinion, that func should compare power of array with number (which should be also power of array)
bool operator< (const Array &arr_to_compare, int number) {
    return arr_to_compare.arr_size < number;
}

// Operator to show array
ostream &operator<< (ostream &out, Array &arr_to_show) {
    for (int i = 0; i < arr_to_show.arr_size; i++)
        out << arr_to_show[i] << " ";
    out << endl;
    return out;
}

int *Array::operator++ (int) {
    for(int i = 0; i < arr_size; i++){
        arr[i]++;
    }
    return arr;
}

// In my opinion, that func should compare power of array with power of another array
bool Array::operator< (const Array& arr_to_comparison) const {
    return arr_size < arr_to_comparison.arr_size;
}

Array Array::operator+ (const Array& arr_to_add) const {
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

    assert(this != &arr_to_add && "Cant assign array to itself");

    delete [] arr;
    arr_size = arr_to_add.arr_size;
    arr = new int [arr_size];
    arr = arr_to_add.arr;
    for(int i = 0; i < arr_size; i++)
        arr[i] = arr_to_add.arr[i];
    return *this;
}
