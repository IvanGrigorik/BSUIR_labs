/*
 * Created by Ivan on 24.11.2021.
 * BSUiR, 2021
 */

#include "menu_functions.h"
#include <algorithm>

int get_menu_choice() {
    system("cls");
    std::cout << "Enter what you want to enter: " << std::endl
              << "1) Add new element to ring" << std::endl
              << "2) Show ring" << std::endl
              << "3) Search in rings" << std::endl
              << "4) Delete from file" << std::endl
              << "5) Compare rings" << std::endl
              << "6) Delete duplicated rings" << std::endl
              << "0) Exit" << std::endl
              << ">> ";
    int choice = get_int(0, 6);
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

void add_element(std::vector<Ring<std::string> > &s_ring_vec) {

    std::cout << std::endl;
    std::cout << "1) Add item to existing ring" << std::endl
              << "2) Add element to new ring" << std::endl << ">> ";
    int choice;
    choice = get_int(1, 2);

    switch (choice) {
        case 1: {
            add_exist(s_ring_vec);
            break;
        }

        case 2: {
            std::cout << std::endl << "Enter new value: ";
            std::string value;
            std::cin >> value;
            Ring<std::string> new_ring(value);
            s_ring_vec.push_back(new_ring);
        }

        default:
            break;
    }
}

void add_exist(std::vector<Ring<std::string> > &s_ring_vec) {

    if (s_ring_vec.empty()) {
        throw std::runtime_error("Not a single ring is created");
    }

    std::cout << "Enter ring number to add info: ";

    int ring_number = get_int(1, static_cast<int>(s_ring_vec.size()));

    if (ring_number > s_ring_vec.size()) {
        throw std::runtime_error("Invalid ring number!");
    }

    std::cout << std::endl << "Enter new value: ";
    std::string value;
    std::cin >> value;

    s_ring_vec[--ring_number].add_back(value);
}

void rings_show(std::vector<Ring<std::string> > &s_ring_vec) {

    if (s_ring_vec.empty()) {
        throw std::runtime_error("Not a single ring is created");
    }
    std::cout << "Rings content: " << std::endl;

    for (int i = 0; i < s_ring_vec.size(); i++) {
        std::cout << std::endl << "Ring " << i + 1 << ":" << std::endl;
        s_ring_vec[i].print();
    }
}

void rings_search(std::vector<Ring<std::string> > &s_ring_vec) {
    rings_show(s_ring_vec);
    std::cout << "Enter value to rings search: ";
    std::string value_to_search;
    std::cin >> value_to_search;

    for (int i = 0; i < s_ring_vec.size(); i++) {
        std::cout << std::endl << "Ring " << i + 1 << ":" << std::endl;

        s_ring_vec[i].find(value_to_search);
    }

    std::cout << std::endl;
}

void rings_delete(std::vector<Ring<std::string> > &s_ring_vec) {
    rings_show(s_ring_vec);

    if (s_ring_vec.empty()) {
        throw std::runtime_error("Not a single ring is created");
    }

    std::cout << std::endl << "Enter ring number to delete info: ";
    int ring_number = get_int(1, static_cast<int>(s_ring_vec.size()));


    std::cout << std::endl << "Enter value to delete: ";
    std::string delete_value;
    std::cin >> delete_value;

    auto it = s_ring_vec[ring_number - 1].find(delete_value);

    if (it.is_valid_iterator()) {
        s_ring_vec[ring_number - 1].delete_element(it);
    }

    delete_ring(s_ring_vec, ring_number);


    std::cout << std::endl << "Value \"" << delete_value << "\" deleted from ring " << ring_number << std::endl;
}

void rings_compare(std::vector<Ring<std::string> > &s_ring_vec) {
    rings_show(s_ring_vec);

    if (s_ring_vec.empty()) {
        throw std::runtime_error("Not a single ring is created");
    }

    std::cout << std::endl << "Enter first ring number to compare: ";
    int ring_number1 = get_int(1, static_cast<int>(s_ring_vec.size()));
    std::cout << std::endl << "Enter second ring number to compare: ";
    int ring_number2 = get_int(1, static_cast<int>(s_ring_vec.size()));

    int compare = compare_elements(s_ring_vec[ring_number1 - 1], s_ring_vec[ring_number2 - 1]);

    if (compare > 0) {
        std::cout << "Ring " << ring_number2 << " bigger than ring " << ring_number1;
    } else if (compare < 0) {
        std::cout << "Ring " << ring_number1 << " bigger than ring " << ring_number2;
    } else if (compare == 0) {
        std::cout << "Rings equal";
    }

}

/* return 1 - if 2nd bigger than 1st
 * return 0 - is rings equal
 * return -1 - if 1st ring bigger than 2nd
 */
template<class T>
int compare_elements(Ring<T> ring_1_to_compare, Ring<T> ring_2_to_compare) {

    int more1 = 0, more2 = 0;

    auto it2 = ring_2_to_compare.begin();
    auto it1 = ring_1_to_compare.begin();

    while (true) {
        if (it1 == ring_1_to_compare.end() || it2 == ring_2_to_compare.end()) {
            break;
        }
        if (it1.get_data().value == it2.get_data().value) {
            ++it1;
            ++it2;
            continue;
        } else if (it1.get_data().value > it2.get_data().value) {
            ++it1;
            ++it2;
            more1++;
        } else if (it2.get_data().value > it1.get_data().value) {
            ++it1;
            ++it2;
            more2++;
        } else {
            break;
        }

    }


    // If one ring is over and the other is not
    if (it1 == ring_1_to_compare.end() && it2 != ring_2_to_compare.end()) {
        return 1;
    }
    if (it2 == ring_2_to_compare.end() && it1 != ring_1_to_compare.end()) {
        return -1;
    }


    if (more1 > more2 + 1) {
        return -1;
    } else if (more2 > more1 + 1) {
        return 1;
    }

    if (it1.get_data().value > it2.get_data().value) {
        return -1;
    } else if (it1.get_data().value < it2.get_data().value) {
        return 1;
    } else if (it1.get_data().value == it2.get_data().value) {
        return 0;
    }

    throw std::runtime_error("Error in compare function");
}

void delete_ring(std::vector<Ring<std::string> > &s_ring_vec, int ring_number) {

    if (s_ring_vec.size() > 1) {
        if (s_ring_vec[ring_number - 1].is_empty()) {
            for (int i = ring_number - 1; i < s_ring_vec.size() - 1; i++) {
                std::swap(s_ring_vec[i], s_ring_vec[i + 1]);
            }
            s_ring_vec.pop_back();
        }
    } else {
        if (s_ring_vec[ring_number - 1].is_empty()) {
            s_ring_vec.pop_back();
        }
    }
}

void delete_duplicated(std::vector<Ring<std::string> > &s_ring_vec) {

    rings_show(s_ring_vec);

    for (int i = 0; i < s_ring_vec.size(); i++) {

        for (int j = i + 1; j < s_ring_vec.size(); j++) {

            if (compare_elements(s_ring_vec[i], s_ring_vec[j]) == 0) {
                std::cout << "Ring " << i + 1 << " and " << j + 1 << " duplicated" << std::endl;

                for (int k = j; k < s_ring_vec.size() - 1; k++) {
                    std::swap(s_ring_vec[k], s_ring_vec[k + 1]);
                }

                s_ring_vec.pop_back();
                --j;
            }
        }
    }
    std::cout << std::endl << "Duplicated rings deleted" << std::endl;
}

