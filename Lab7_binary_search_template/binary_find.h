//
// Created by Ivan on 10.10.2021.
//

#ifndef LAB7_BINARY_SEARCH_TEMPLATE_BINARY_FIND_H
#define LAB7_BINARY_SEARCH_TEMPLATE_BINARY_FIND_H

#include <iostream>
#include <cstring>

using namespace std;

template<typename T, int len>
void bin_find(const T *array, T key) {
    if (array[0] == key) {
        cout << "Index of \"" << key << "\" in array is " << 0 << endl;
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
            cout << "Index of \"" << key << "\" in array is " << mid << endl;
            return;
        }
    }
    cout << "The array does not have element " << key << endl;
}

template<int len>
void bin_find(char **str, const char *key) {
    if (strcmp (str[0], key) == 0) {
        cout << "Index of \"" << key << "\" in array is 0";
        return;
    }

    int left = 0;
    int right = len - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (strcmp (str[mid], key) < 0) {
            left = mid + 1;
        } else if (strcmp (str[mid], key) > 0) {
            right = mid - 1;
        } else {
            cout << "Index of \"" << key << "\" in array is " << mid << endl;
            return;
        }
    }

    cout << "The array does not have element " << key << endl;
}

#endif //LAB7_BINARY_SEARCH_TEMPLATE_BINARY_FIND_H
