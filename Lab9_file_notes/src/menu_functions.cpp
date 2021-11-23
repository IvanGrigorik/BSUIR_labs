/*
 * Created by Ivan on 23.11.2021.
 * BSUiR, 2021
 */

#include "menu_functions.h"

int get_menu_choice() {

    system("cls");
    std::cout << "Enter what you want to enter: " << std::endl
              << "1) Add new element to .txt file" << std::endl
              << "2) Add new element to .bin file" << std::endl
              << "3) Show .txt file" << std::endl
              << "4) Show .bin file" << std::endl
              << "5) Reverse show .txt file" << std::endl
              << "6) Reverse show .bin file" << std::endl
              << "7) Search in .txt file" << std::endl
              << "8) Search in .bin file" << std::endl
              << "9) Delete from .txt file" << std::endl
              << "10) Delete from .bin file" << std::endl
              << "11) Delete duplicated" << std::endl
              << "12) Copy set in .txt file" << std::endl
              << "13) Copy set in .bin file" << std::endl
              << "0) Exit" << std::endl
              << ">> ";

    int choice = get_int(0, 13);
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

void add_file(std::ofstream &file, const std::string &file_type) {
    std::string note_title, note_text;
    int is_complete;
    std::cout << std::endl << "Enter note title: ";
    std::cin >> note_title;
    std::cout << "Enter note text: ";
    std::cin >> note_text;
    std::cout << "Enter is note complete ( 0 - note complete, 1 - complete): ";
    is_complete = get_int(0, 1);

    Notes temp(note_title, note_text, static_cast<bool>(is_complete));

    if (file_type == "text") {
        temp.write_text(file);
    } else if (file_type == "binary") {
        temp.write_bin(file);
    }
    file.close();
}

void search_file(std::ifstream &file, const std::string &file_type) {
    std::cout << "Enter what the search will be: " << std::endl
              << "1) By note name" << std::endl
              << "2) By note text" << std::endl
              << "3) By progress status" << std::endl;
    int choice;
    choice = get_int(1, 3);

    std::string search_string;
    int search_bool;

    switch (choice) {

        case 1: {
            std::cout << "Enter note name to search: ";
            std::cin >> search_string;
            file_searching(file_type, file, search_string, 1);
            break;
        }

        case 2: {
            std::cout << "Enter note text to search: ";
            std::cin >> search_string;
            file_searching(file_type, file, search_string, 2);
            break;
        }

        case 3: {
            std::cout << "Enter note progress status to search" << std::endl
                      << "(0 - not complete, 1 - complete): ";
            search_bool = get_int(0, 1);
            search_string = search_bool == 0 ? "false" : "true";
            file_searching(file_type, file, search_string, 3);
            break;
        }

        default: {
            break;
        }
    }
}

void delete_file_func(std::ifstream &file, const std::string &file_type) {

    std::cout << std::endl << std::endl;

    if (file_type == "text") {
        file.open(text);
        print_text(file);
    } else if (file_type == "binary") {
        file.open(binary, std::ios::in);
        print_binary(file);
    }

    std::cout << "Enter the number to be deleted: ";

    int delete_number;
    std::cin >> delete_number;

    file_delete(file_type, file, delete_number);

    file.close();
}

void copy_strings_txt(std::ifstream &file) {
    std::cout << std::endl;

    if (!file.is_open()) {
        file.open(text);
    }

    print_text(file);

    int first_line, last_line, copy_location;
    std::cout << "Enter first lane to copy: ";
    first_line = get_int(0, INT_MAX);

    std::cout  << "Enter last lane to copy: ";
    last_line = get_int(0, INT_MAX);

    std::cout  << "Enter copy location: ";
    copy_location = get_int(0, INT_MAX);

    copy_txt(file, first_line, last_line, copy_location);

    file.close();
}

void copy_strings_bin(std::ifstream &file){
    std::cout << std::endl;

    if (!file.is_open()) {
        file.open(binary, std::ios::binary | std::ios::in | std::ios::out);
    }

    print_binary(file);

    int first_line, last_line, copy_location;
    std::cout << "Enter first lane to copy: ";
    first_line = get_int(0, INT_MAX);

    std::cout  << "Enter last lane to copy: ";
    last_line = get_int(0, INT_MAX);

    std::cout  << "Enter copy location: ";
    copy_location = get_int(0, INT_MAX);

    copy_bin(file, first_line, last_line, copy_location);
    file.close();
}