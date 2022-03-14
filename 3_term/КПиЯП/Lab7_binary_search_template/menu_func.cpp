//
// Created by Ivan on 27.10.2021.
//

#include "menu_func.h"
#include <iostream>
#include <cassert>

int get_menu_choice() {
    system ("cls");
    std::cout << "Enter what you want to enter: " << std::endl
              << "1) Add new element to array " << std::endl
              << "2) Show array" << std::endl
              << "3) Sort array" << std::endl
              << "4) Find element in array (array must be sorted)" << std::endl
              << "0) Exit" << std::endl
              << ">> ";

    int choice = get_int (0, 4);
    return choice;
}

int get_int(int min_size, int max_size) {
    int x;

    while (true) {
        std::cin >> x;

        if (std::cin.fail () || std::cin.peek () != '\n' || x < min_size || x > max_size) {
            std::cout << "Invalid input, try again" << std::endl << ">> ";
            std::cin.clear ();
            std::cin.ignore (32768, '\n');
        } else {
            return x;
        }
    }
}


void get_array_element(Array &arr_to_get) {
    std::cout << "Enter new element: ";
    wchar_t new_element;

    while (true) {
        std::wcin >> new_element;

        if (std::wcin.fail () || std::wcin.peek () != '\n' || new_element < 33 || new_element > 126) {
            std::cout << "Invalid input, try again" << std::endl << ">> ";
            std::wcin.clear ();
            std::wcin.ignore (80000, '\n');
        } else {
            break;
        }
    }

    if (!(arr_to_get.array = (wchar_t *) realloc (arr_to_get.array, sizeof (wchar_t) * (arr_to_get.total + 1)))) {
        assert("Memory allocation fail");
    }


    arr_to_get.array[arr_to_get.total] = new_element;
    arr_to_get.total++;

    if (arr_to_get.total > 1 && (arr_to_get.array[arr_to_get.total - 1] < arr_to_get.array[arr_to_get.total - 2])) {
        arr_to_get.is_sorted = false;
    }
}

void show_arr(Array arr_to_show) {
    if(!arr_to_show.total){
        std::cout << "No elements in array!";
        system("pause > 0");
        return;
    }
    for (int i = 0; i < arr_to_show.total; i++) {
        std::wcout << arr_to_show.array[i] << ' ';
    }

    std::cout << std::endl;
}

void sort(Array &arr_to_sort) {

    for (int i = 0; i < arr_to_sort.total; i++) {
        for (int j = 0; j < arr_to_sort.total - 1; j++) {

            if (arr_to_sort.array[j] > arr_to_sort.array[j + 1]) {
                wchar_t temp = arr_to_sort.array[j];
                arr_to_sort.array[j] = arr_to_sort.array[j + 1];
                arr_to_sort.array[j + 1] = temp;
            }

        }
    }

    std::cout << "Sort success" << std::endl;
    arr_to_sort.is_sorted = true;
}