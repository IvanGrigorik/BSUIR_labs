//
// Created by Ivan on 19.10.2021.
//

#include "Set.h"

template<class T>
Set<T>::Set(const Set<T> &to_copy) {
    info_array = to_copy.info_array;
    std::cout << "Set copy constructor" << std::endl;
}

template<class T>
void Set<T>::add(T new_obj) {
    if(this->index >= Set::SIZE)
        throw Set_ex("Index error");
    index++;
    info_array[index] = new_obj;
}
