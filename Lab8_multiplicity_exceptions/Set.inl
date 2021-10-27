//
// Created by Ivan on 19.10.2021.
//

#include "Set.h"

// Constructors and destructor


template<class T>
void Set<T>::clear() {
    if (is_empty ()) {
        std::cout << "Set is empty";
        system ("pause > 0");
        return;
    }

    for (auto &i: info_array) {
        i = 0;
    }
    max_index = -1;
}


// Methods
template<class T>
void Set<T>::add(T new_obj) {
    max_index++;
    if (is_full ()) {
        max_index--;
        throw Set_ex ("Index error");
    }
    for (int i = 0; i < max_index; i++) {
        if (info_array[i] == new_obj) {
            std::cout << "This element is already in the set" << std::endl;
            system ("pause > 0");
            max_index--;
            return;
        }
    }
    info_array[max_index] = new_obj;
}

template<class T>
void Set<T>::show() const {
    if (is_empty ()) {
        std::cout << "Set is empty";
        system ("pause > 0");
        return;
    }

    for (int i = 0; i <= max_index; i++) {
        std::cout << info_array[i] << ' ';
    }
    std::cout << std::endl;
    system ("pause > 0");
}

template<class T>
bool Set<T>::is_full() const {
    return max_index >= Set::SIZE;
}

template<class T>
bool Set<T>::is_empty() const {
    return max_index <= -1;
}

// Overloads operators
template<class T>
bool Set<T>::operator==(const Set<T> &another_set) const {
    if (max_index != another_set.max_index)
        return false;

    bool is_equal = true;
    for (int i = 0; i <= max_index; i++) {
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


//template<class T>
//void Set<T>::add(const Set<T> &another_set) {
//    max_index = max_index > another_set.max_index ? max_index : another_set.max_index;
//
//    for (int i = 0; max_index; i++) {
//        info_array[i] += another_set.info_array[i];
//    }
//}


template<class T>
void Set<T>::delete_element() {

    if (is_empty ()) {
        std::cout << "Set is empty";
        system ("pause > 0");
        return;
    }

    show ();
    std::cout << std::endl << "What element you want to delete?" << std::endl << ">> ";
    int element_to_delete (get_int (INT_MIN, INT_MAX));

    for (int i = 0; i <= max_index; i++) {
        if (info_array[i] == element_to_delete) {
            for (int j = i; j < max_index; j++) {
                info_array[j] = info_array[j + 1];
            }
            max_index--;
            std::cout << "Delete process success";
            system ("pause > 0");
            return;
        }
    }

    std::cout << "No such element to delete";
    system ("pause > 0");
}

template<class T>
void Set<T>::search() const {

    if (is_empty ()) {
        std::cout << "Set is empty";
        system ("pause > 0");
        return;
    }

    show ();
    std::cout << std::endl << "Enter number to search" << std::endl << ">> ";
    int num_to_search (get_int (INT_MIN, INT_MAX));

    for (int i = 0; i <= max_index; i++) {
        if (info_array[i] == num_to_search) {
            std::cout << num_to_search << " index: " << i;
            system ("pause > 0");
            return;
        }
    }

    std::cout << "There is no element " << num_to_search << " in the given Set" << std::endl;
    system ("pause > 0");
}



