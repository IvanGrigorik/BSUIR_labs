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
            << "4) Delete element in Set" << std::endl
            << "5) To clear Set" << std::endl
            << "6) Add one set to another" << std::endl
            << "7) Sort set (Shell sort)" << std::endl
            << "8) Get avg in set" << std::endl
            << "9) Change some element" << std::endl
            << "0) Exit" << std::endl
            << ">> ";
    int choice = get_int (0, 9);
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
