//
// Created by Ivan on 17.10.2021.
//

#include "getters.h"

int get_int (int max_size) {
    int x;
    while (true) {
        std::cin >> x;

        if (std::cin.fail() || std::cin.peek() != '\n' || x < 0 || x > max_size) {
            std::cout << "Invalid input, try again" << std::endl << ">> ";
            std::cin.clear();
            std::cin.ignore(32768, '\n');
        } else {
            return x;
        }
    }
}

std::string get_string (const std::string &code) {
    std::string name;
    while (true) {
        std::cin >> name;
        if (std::cin.fail() || std::cin.bad()) {
            std::cout << "Invalid input!" << std::endl << ">>";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        } else if (std::cin.peek() != '\n') {
            std::cout << "Enter one word!" << std::endl << ">> ";
            std::cin.ignore(1000, '\n');
        } else {
            bool is_good = true;
            for (auto &item: name) {
                if (!std::islower(item) && !std::isupper(item)) {
                    std::cout << "Invalid input! " << std::endl << ">> ";
                    std::cin.ignore(1000, '\n');
                    is_good = false;
                    break;
                }
            }
            if (is_good) {
                break;
            }
        }
    }

    return name;
}