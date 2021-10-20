//
// Created by Ivan on 20.10.2021.
//

#include "menu_functions.h"
#include <iostream>

int get_menu_choice() {
    system ("cls");
    std::cout
            << "Enter what you want to enter: " << std::endl
            << "1) Add new number to Set" << std::endl
            << "2) Show Set" << std::endl
            << "3) Search element in Set" << std::endl
            << "0) Exit" << std::endl
            << ">> ";

    int choice = get_int (0, 3);
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
