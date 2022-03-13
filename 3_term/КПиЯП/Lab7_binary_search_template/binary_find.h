//
// Created by Ivan on 10.10.2021.
//

#ifndef LAB7_BINARY_SEARCH_TEMPLATE_BINARY_FIND_H
#define LAB7_BINARY_SEARCH_TEMPLATE_BINARY_FIND_H

#include <iostream>

template<typename T>
void bin_find(const T *array, T key, int len) {
    if (array[0] == key) {
        std::cout << "Index of \"" << key << "\" in array is " << 0 << std::endl;
        return;
    }

    int left = 0;
    int right = len - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (array[mid] < key) {
            left = mid + 1;
        } else if (array[mid] > key) {
            right = mid - 1;
        } else {
            std::cout << "Index of \"" << key << "\" in array is " << mid << std::endl;
            return;
        }
    }
    std::cout << "The array does not have element " << key << std::endl;
}

// Function to find wchar_t symbols
template<typename>
void bin_find(const wchar_t *array_c, const wchar_t key, int len) {
    if (array_c[0] == key) {
        std::wcout << "Index of \"" << key << "\" in array is 0";
        return;
    }

    int left = 0;
    int right = len - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (array_c[mid] < key) {
            left = mid + 1;
        } else if (array_c[mid] > key) {
            right = mid - 1;
        } else {
            std::wcout << "Index of \"" << key << "\" in array is " << mid << std::endl;
            return;
        }
    }

    std::wcout << "The array does not have element " << key << std::endl;
}

#endif //LAB7_BINARY_SEARCH_TEMPLATE_BINARY_FIND_H
