/*
 * Created by Ivan on 24.11.2021.
 * BSUiR, 2021
 */

#include "menu_functions.h"

int get_menu_choice() {
    system("cls");
    std::cout << "Enter what you want to enter: " << std::endl
              << "1) Add new element to ring" << std::endl
              << "2) Show ring" << std::endl
              << "3) "
              << "0) Exit" << std::endl
              << ">> ";
    int choice = get_int(0, 9);
    return choice;
}


int get_int(int min_size, int max_size) {
    int x;
    while (true) {
        std::cin >> x;

        if (std::cin.fail() || std::cin.peek() != '\n' || x < min_size || x > max_size) {
            std::cout << "Invalid input, try again" << std::endl << ">> ";
            std::cin.clear();
            std::cin.ignore(32768, '\n');
        } else {
            return x;
        }
    }
}

void program() {
    Ring<std::string> s_ring;

    while (true) {
        try {
            switch (get_menu_choice()) {

                case 1: {
                    std::cout << "Enter element to add: ";
                    std::string element_to_add;
                    std::cin >> element_to_add;

                    s_ring.add_back(element_to_add);
                    break;
                }

                case 2: {
                    std::cout << "Ring content: " << std::endl;
                    s_ring.print();
                    system("pause > 0");
                    break;
                }

                case 3: {

                }

                case 0:
                    exit(EXIT_SUCCESS);
            }
        } catch (std::exception &ex) {
            std::cout << "Error: " << ex.what() << std::endl;
        }

        system("cls");
    }
}