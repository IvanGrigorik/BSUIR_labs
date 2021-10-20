//
// Created by Ivan on 19.10.2021.
//

#include "Set.h"

// Constructors and destructor
template<class T>
Set<T>::Set() {
    for (auto &i: info_array) {
        i = 0;
    }
    max_index = -1;
    std::cout << "Set default constructor" << std::endl;
}

template<class T>
Set<T>::Set(const Set<T> &to_copy) {
    if (!(info_array = to_copy.info_array))
        throw Set_ex ("Copy constructor error");
    std::cout << "Set copy constructor" << std::endl;
}

template<class T>
void Set<T>::clear() {
    for (auto &i: info_array) {
        i = 0;
    }
    max_index = 0;
}


// Methods
template<class T>
void Set<T>::add(T new_obj) {
    max_index++;
    if (is_full ()) {
        max_index--;
        throw Set_ex ("Index error");
    }
    info_array[max_index] = new_obj;
}

template<class T>
void Set<T>::show() const {
    if (this->is_empty ()) {
        std::cout << "Set is empty";
        return;
    }

    for (int i = 0; i <= max_index; i++) {
        std::cout << info_array[i] << ' ';
    }
}

template<class T>
bool Set<T>::is_full() const {
    return max_index >= Set::SIZE;
}

template<class T>
bool Set<T>::is_empty() const {
    return max_index < 0;
}

// Overloads operators
template<class T>
bool Set<T>::operator==(const Set<T> &another_set) const {
    if (this->max_index != another_set.max_index)
        return false;

    bool is_equal = true;
    for (int i = 0; i < max_index; i++) {
        if (another_set.info_array[i] != info_array[i]) {
            is_equal = false;
            break;
        }
    }

    return is_equal;
}

template<class T>
bool Set<T>::operator!=(const Set<T> &another_set) const {
    return !operator== (another_set);
}

template<class T>
Set<T> Set<T>::operator+(const Set<T> &another_set) const {

    Set new_set;
    int new_max_index = max_index > another_set.max_index ? max_index : another_set.max_index;

    for (int i = 0; i < new_max_index; i++) {
        new_set.info_array[i] = info_array[i] + another_set.info_array[i];
    }
    return new_set;
}

template<class T>
void Set<T>::delete_element() {
    show ();
    std::cout << "What element you want to delete?" << std::endl << ">> ";
    int choice (get_int (0, max_index));


}

template<class T>
void Set<T>::search() const {

    if (is_empty ()) {
        std::cout << "Empty Set!";
        return;
    }

    std::cout << "Enter number to search" << std::endl << ">> ";
    int num_to_search (get_int (INT_MIN, INT_MAX));

    for (int i = 0; i <= max_index; i++) {
        if (info_array[i] == num_to_search) {
            std::cout << num_to_search << " index: " << i;
            system ("pause > 0");
            return;
        }
    }

    std::cout << "There is no element" << num_to_search << " in the given Set" << std::endl;
    system ("pause > 0");
}
