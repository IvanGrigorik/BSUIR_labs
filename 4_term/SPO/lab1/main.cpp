#include "functions.h"


int main(int argc, char * argv[]) {

    std::string dir = get_dir_to_walk(argc, argv);
    Flags flags =  parse_flags(argc, argv);


    std::vector<File> files;
    collect_files(dir, files);
    show_files(files, flags);

}
