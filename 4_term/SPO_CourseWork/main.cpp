#include "functions.h"

int main(int argc, char *argv[]) {

    std::string dir_to_walk = (argc == 1 || argv[1][0] == '-') ? "." : argv[1];
    flags_t flags;
    flags = parse_flags(argc, argv);

    try {
        std::vector<file_data_t> unique_files{};
        std::vector<file_to_delete_t> duplicated_files{};

        collect_files(dir_to_walk, unique_files, duplicated_files, flags);

        files_output(unique_files, duplicated_files, flags);

        if(flags.delete_flag){
            delete_files(duplicated_files);
        }
    } catch (std::exception &e) {
        std::cout << e.what();
    }

    return 0;
}
