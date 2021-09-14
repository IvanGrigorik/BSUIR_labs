//
// Created by Ivan on 14.09.2021.
//

#ifndef LAB3_INT_ARRAY_OVERLOAD_ARRAY_SIZE_H
#define LAB3_INT_ARRAY_OVERLOAD_ARRAY_SIZE_H

#include <ostream>

class Array_size {
private:
    int arr_size;

public:
    // Simply constructor
    explicit Array_size (int size);

    // Overloaded output
    friend std::ostream &operator<< (std::ostream &out, const Array_size &array_size_to_out);
};


#endif //LAB3_INT_ARRAY_OVERLOAD_ARRAY_SIZE_H
