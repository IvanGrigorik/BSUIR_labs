//
// Created by Ivan on 17.10.2021.
//

#include "getters.h"

int get_int (int max_size) {
    int x;
    while (true) {
        std::cin >> x;

        if (std::cin.fail() || std::cin.peek() != '\n' || x < 0 || x > max_size) {
            std::cout << "Invalid input, try again" << std::endl << ">>";
            std::cin.clear();
            std::cin.ignore(32768, '\n');
        } else {
            return x;
        }
    }
}

std::string get_string (const std::string &code) {
    std::string new_string;
    while (true) {
        std::cin >> new_string;
        if (std::cin.fail() || std::cin.bad()) {
            std::cout << "Invalid input" << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        } else if (std::cin.peek() != '\n') {
            std::cout << "Enter single word" << std::endl;
            std::cin.ignore(10000, '\n');
        } else {
            return new_string;
        }
    }
}