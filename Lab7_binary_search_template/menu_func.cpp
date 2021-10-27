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
              << "4) Find element in array" << std::endl
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
    char new_element;

    while (true) {
        std::cin >> new_element;

        if (std::cin.fail () || std::cin.peek () != '\n') {
            std::cout << "Invalid input, try again" << std::endl << ">> ";
            std::cin.clear ();
            std::cin.ignore (32768, '\n');
        } else {
            break;
        }
    }

    if (!(arr_to_get.arr_c = (char *) realloc (arr_to_get.arr_c, arr_to_get.total + 1))) {
        assert("Memory allocation fail");
    }
    arr_to_get.arr_c[arr_to_get.total] = new_element;
    arr_to_get.total++;
}

void show_arr(Array arr_to_show) {
    for (int i = 0; i < arr_to_show.total; i++) {
        std::cout << arr_to_show.arr_c[i] << ' ';
    }

    std::cout << std::endl;
    system ("pause > 0");
}

void sort(Array &arr_to_sort) {

    for (int i = 0; i < arr_to_sort.total; i++) {
        for (int j = 0; j < arr_to_sort.total - 1; j++) {

            if (arr_to_sort.arr_c[j] > arr_to_sort.arr_c[j + 1]) {
                char temp = arr_to_sort.arr_c[j];
                arr_to_sort.arr_c[j] = arr_to_sort.arr_c[j + 1];
                arr_to_sort.arr_c[j + 1] = temp;
            }

        }
    }

    std::cout << "Sort success" << std::endl;
    system ("pause > 0");
}