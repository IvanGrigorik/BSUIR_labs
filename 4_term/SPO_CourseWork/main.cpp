#include "functions.h"



// Print the MD5 sum as hex-digits.
void print_md5_sum(unsigned char *md) {
    int i;
    for (i = 0; i < MD5_DIGEST_LENGTH; i++) {
        printf("%02x", md[i]);
    }
}


int main([[maybe_unused]] int argc, char *argv[]) {
    // Create files map, which contain MD5 hash as key and file name as value
    std::map<std::string , std::string> files_map;

    collect_files(argv[1], files_map);

    std::cout << std::endl << std::endl;
    for (auto &i: files_map) {
        std::cout << "File : " << i.second << "; Hash: " << i.first << std::endl;
    }

    return 0;
}
