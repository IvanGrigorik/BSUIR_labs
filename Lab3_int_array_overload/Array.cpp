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
Array operator-- (Array &arr_to_subtract) {
    assert(arr_to_subtract.arr_size > 0 && "Invalid array index!");
    for (int i = 0; i < arr_to_subtract.arr_size; i++) {
        arr_to_subtract[i]--;
    }
    return arr_to_subtract;
}

// Operator to add number to every number from the array
Array operator+ (Array &arr_to_add_number, int number) {
    for (int i = 0; i < arr_to_add_number.arr_size; i++) {
        arr_to_add_number[i] += number;
    }
    return arr_to_add_number;
}

// In my opinion, that func should compare power (size) of array with number (which should be also power of array)
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
    for (int i = 0; i < arr_size; i++) {
        arr[i]++;
    }
    return arr;
}

// In my opinion, that func should compare one array with another, and if power of arrays
// are not same - they should return false

// Realization is shitty
bool Array::operator< (const Array &arr_to_comparison) const {
    if (arr_size < arr_to_comparison.arr_size)
        return false;
    bool is_more = false;
    for (int i = 0; i < arr_size; i++) {
        if(arr[i] < arr_to_comparison.arr[i])
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

    assert(this != &arr_to_add && "Cant assign array to itself");

    delete[] arr;
    arr_size = arr_to_add.arr_size;
    arr = new int[arr_size];
    arr = arr_to_add.arr;
    for (int i = 0; i < arr_size; i++)
        arr[i] = arr_to_add.arr[i];
    return *this;
}
