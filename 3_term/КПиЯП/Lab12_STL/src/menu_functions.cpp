/*
 * Created by Ivan on 29.11.2021.
 * BSUiR, 2021
 */

#include "menu_functions.h"

int get_menu_choice() {
    system("cls");
    std::cout << "Enter what you want to enter: " << std::endl
              << "1) Add new string to file" << std::endl
              << "2) Show source file" << std::endl
              << "3) Show target file" << std::endl
              << "4) Search words without symbols" << std::endl
              << "5) Search words with symbols" << std::endl
              << "6) Delete duplicated strings" << std::endl
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

void add_new_string(std::ofstream &source, bool is_first) {
    if (!source.is_open()) {
        source.open(source_filename, std::ios::app);
    }

    std::cin.ignore(1000, '\n');

    std::string str_to_add;
    std::cout << "Enter string to add: ";

    std::cin.unsetf(std::ios::skipws);
    std::getline(std::cin, str_to_add);

    if (!is_first) {
        source << '\n';
    }

    source << str_to_add;

    source.close();
}

void show_source(std::ifstream &source) {
    if (!source.is_open()) {
        source.open(source_filename);
    }

    std::cin.ignore(1000, '\n');

    std::string str;
    while (!source.eof()) {
        getline(source, str, '\n');
        std::cout << str << std::endl;
    }
    source.close();
}

void show_target(std::ifstream &target) {
    if (!target.is_open()) {
        target.open(target_filename);
    }
    std::cin.ignore(1000, '\n');

    std::string str;
    while (!target.eof()) {
        getline(target, str, '\n');
        std::cout << str << std::endl;
    }
    target.close();
}

void search_without(std::ifstream &source) {
    if (!source.is_open()) {
        source.open(source_filename);
    }
    std::cin.ignore(1000, '\n');

    std::string to_find;
    std::cout << "Enter symbol(s) to check: ";
    std::cin >> to_find;

    // Variables to count how many words without ... in file
    int find_words_number{};
    int words_number{};

    std::ofstream target;
    target.open(target_filename, std::ios::trunc);

    bool is_first = true;

    while (!source.eof()) {
        // Get string from file.
        std::string string_to_check{};
        std::getline(source, string_to_check, '\n');

        // Split string into single words stream.
        std::istringstream words_stream(string_to_check);

        for (std::string word; words_stream >> word;) {

            // Cycles to match each find string symbol to each word symbol.
            for (auto find_symbol: to_find) {

                // Use algorithm to find each symbol from given symbol set.
                size_t found = word.find(find_symbol);
                if (found != std::string::npos) {
                    find_words_number++;
                    break;
                }
            }
            words_number++;
        }
        std::cout << std::endl << "Count words without [" << to_find << "]" << " in string \"" << string_to_check
                  << "\": " << words_number - find_words_number << std::endl;

        if (!is_first) {
            target << '\n';
        } else {
            is_first = false;
        }

        target << words_number - find_words_number;

        words_number = 0;
        find_words_number = 0;
    }

    source.close();
}

void search_with(std::ifstream &source) {
    if (!source.is_open()) {
        source.open(source_filename);
    }
    std::cin.ignore(1000, '\n');

    std::string to_find;
    std::cout << "Enter string to find: ";
    std::cin >> to_find;

    while (!source.eof()) {
        // Get string from file.
        std::string string_to_check{};
        std::getline(source, string_to_check, '\n');

        // Split string into single words stream.
        std::istringstream words_stream(string_to_check);

        std::cout << std::endl << "Words with [" << to_find << "]" << " in string \"" << string_to_check << "\": ";
        for (std::string word; words_stream >> word;) {

            // Use algorithm to find each symbol from given symbol set.
            size_t found = word.find(to_find);

            if (found != std::string::npos) {
                std::cout << word << ' ';
            }
        }
    }

    source.close();
}

void delete_duplicated(std::ifstream &source) {
    if (!source.is_open()) {
        source.open(source_filename);
    }

    std::vector<std::string> file_strings;

    while (!source.eof()) {
        // Get string from file.
        std::string string_to_check{};
        std::getline(source, string_to_check, '\n');
        file_strings.push_back(string_to_check);
    }

    for (int i = 0; i < file_strings.size(); i++) {
        for (int j = i + 1; j < file_strings.size(); j++) {

            if (file_strings[i] == file_strings[j]) {

                for (int k = j; k < file_strings.size() - 1; k++) {
                    std::swap(file_strings[k], file_strings[k + 1]);
                }

                file_strings.pop_back();
                --j;
            }
        }
    }

    source.close();
    std::ofstream source_o;
    source_o.open(source_filename, std::ios::trunc);

    for (int i = 0; i < file_strings.size(); i++) {
        if (i != 0) {
            source_o << '\n';
        }
        source_o << file_strings[i];
    }

    std::cin.ignore(1000, '\n');
    std::cout << "Duplicated strings deleted";
    source_o.close();
}