#include "functions.h"

int main([[maybe_unused]] int argc, char *argv[]) {
    // Create files map, which contain MD5 hash as key and file name as value
    try {
        std::map<std::string, std::string> files_map;

        std::vector<file_data_t> unique_files{};
        std::vector<file_to_delete_t> duplicated_files{};

        collect_files(argv[1], unique_files, duplicated_files, ' ');

        std::cout << std::endl << std::endl;

        std::cout << "Unique files: " << std::endl;
        for (auto &i: unique_files) {
            std::cout << "File name: " << i.file_name << std::endl
                      << "File hash: " << i.file_hash << std::endl << std::endl;
        }

        std::cout << "Duplicated files: " << std::endl;
        for (auto &i: duplicated_files) {
            std::cout << "File name: " << i.file_name << std::endl
                      << "File directory: " <<  i.file_path << std2::endl;
        }

    } catch (std::exception &e) {
        std::cout << e.what();
    }

    return 0;
}
