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

    // Counter to find words and for all words
    int find_words_number{};
    int words_number{};

    std::cout << "Words without [" << to_find << "]: ";

    // Cycle while words stream have words.
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

    std::cout << std::endl << "Count words without [" << to_find << "]: " << words_number - find_words_number;

    std::ofstream target(target_filename, std::ios::trunc);
    target << words_number - find_words_number << '\n';
}