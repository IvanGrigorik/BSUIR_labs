#include <iostream>
#include <fstream>
#include <list>

#include <sstream>

// Filenames.
constexpr char source_filename[] = "source.txt";
constexpr char target_filename[] = "target.txt";


int main() {
    std::cout << "Source file: " << source_filename << std::endl;
    std::cout << "Target file: " << target_filename << std::endl;

    // Open source file.
    std::ifstream source(source_filename, std::ios::in);

    // Get string from file.
    std::string string_to_check{};
    std::getline(source, string_to_check);

    std::cout << "File string: " << string_to_check << std::endl;

    // Split string into single words stream.
    std::istringstream words_stream(string_to_check);

    // User input.
    std::string to_find;
    std::cout << "Enter symbol(s) to check: ";
    std::cin >> to_find;

    // Flag to check single word (if we have 1 letter from "to_find" string, we break cycle and go to another word).
    bool flag;
    // Counter to find words and for all words
    int find_words_number{};
    int words_number{};

    std::cout << "Words without [" << to_find << "]: ";

    // Cycle while words stream have words.
    for (std::string word; words_stream >> word;) {

        // Flag to check, is word contain any symbol from given set.
        flag = false;

        // Cycles to match each find string symbol to each word symbol.
        for (auto find_symbol: to_find) {
            for (auto word_symbol: word) {
                if (find_symbol == word_symbol) {
                    flag = true;
                    find_words_number++;
                    break;
                }
            }
            if (flag)
                break;
        }

        if (!flag) {
            std::cout << word << ' ';
        }
        words_number++;
    }

    std::cout << std::endl << "Count words without [" << to_find << "]: " << words_number - find_words_number;

    std::ofstream target(target_filename, std::ios::trunc);
    target << words_number - find_words_number << '\n';
}