//
// Created by Ivan on 19.10.2021.
//

#include "Set.h"
#include <cmath>

// Constructor
template<class T>
void Set<T>::clear() {
    if (is_empty ()) {
        throw Set_ex ("Set is empty");
    }

    for (auto &i: info_array) {
        i = 0;
    }
    // Minus one, 'cause when we add 1st element, he will have 0th index
    max_index = -1;
}


// Checker-s is set full or empty
template<class T>
bool Set<T>::is_full() const {
    return max_index >= Set::SIZE;
}

template<class T>
bool Set<T>::is_empty() const {
    return max_index <= -1;
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
        throw Set_ex ("Set is empty");
    }

    for (int i = 0; i <= max_index; i++) {
        std::cout << info_array[i] << ' ';
    }
    std::cout << std::endl;
    system ("pause > 0");
}


template<class T>
void Set<T>::delete_element() {
    if (is_empty ()) {
        throw Set_ex ("Set is empty");
    }

    show ();
    std::cout << std::endl << "What element you want to delete?" << std::endl << ">> ";
    T element_to_delete (get_int (INT_MIN, INT_MAX));

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
        throw Set_ex ("Set is empty");
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

template<class T>
void Set<T>::shell_sort() {
    if (is_empty ()) {
        throw Set_ex ("Set is empty");
    }

    for (int gap = max_index + 1; gap > 0; gap /= 2) {
        for (int i = gap; i < max_index + 1; i++) {
            T temp = info_array[i];

            int j;

            for (j = i; j >= gap && info_array[j - gap] > temp; j -= gap) {
                info_array[j] = info_array[j - gap];
            }

            info_array[j] = temp;
        }
    }
    std::cout << "Success sort!" << std::endl;
}

template<class T>
void Set<T>::avg() const {
    if (is_empty ()) {
        throw Set_ex ("Set is empty");
    }

    float all;

    for (int i = 0; i < max_index + 1; i++) {
        all += info_array[i];
    }

    double avg = all / (max_index + 1);

    double integer_part;
    modf (avg, &integer_part);

    if (integer_part != avg) {
        throw Set_ex ("The avg number in not an integer");
    }

    std::cout << "avg in set is: " << avg;
}

template<class T>
void Set<T>::change() {
    if (is_empty ()) {
        throw Set_ex ("Set is empty");
    }

    show ();
    std::cout << std::endl << "Enter number to change" << std::endl << ">> ";
    T num_to_change (get_int (INT_MIN, INT_MAX));

    bool is_have = false;

    int index = 0;

    for (int i = 0; i <= max_index; i++) {
        if (info_array[i] == num_to_change) {
            is_have = true;
            index = i;
        }
    }

    if (!is_have) {
        std::cout << "There is no element " << num_to_change << " in the given Set" << std::endl;
        system ("pause > 0");
        return;
    } else {
        std::cout << std::endl << "Enter new element" << std::endl << ">> ";
        T new_element;
        std::cin >> new_element;
        for (int i = 0; i <= max_index; i++) {
            if (info_array[i] == new_element) {
                throw Set_ex ("This element is already exist!");
            }
        }
        info_array[index] = new_element;
        std::cout << "Change success";
    }
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
