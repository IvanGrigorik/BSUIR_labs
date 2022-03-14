//
// Created by Ivan on 14.09.2021.
//

#include "Array_size.h"

Array_size::Array_size (int size) {
    this->arr_size = size;
}

std::ostream &operator<< (std::ostream &out, const Array_size &array_size_to_out) {
    out << "Array size: " << array_size_to_out.arr_size;
    return out;
}


