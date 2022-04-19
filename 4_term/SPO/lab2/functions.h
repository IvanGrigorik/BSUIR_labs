//
// Created by sifi on 13.02.2022.
//

#ifndef LAB1_FUNCTIONS_H
#define LAB1_FUNCTIONS_H

// header library's
#include <functional>
#include <string>
#include <dirent.h>
#include <vector>

// .cpp library's
#include <iostream>
#include <unistd.h>
#include <iomanip>
#include <cstring>
#include <algorithm>

// Work with flag to right output settings
struct Flags {
    bool l{}, d{}, f{}, s{};
};

Flags parse_flags(int argc, char *argv[]);


// Work with files (create file structure)
struct File {
    enum Type {
        DIR, LINK, FILE, etc
    } type{etc};

    std::string name;

    File(int type, const std::string &name); // !!!
};

bool operator<(const File &first_file, const File &second_file);

void collect_files(std::string current_dir, std::vector<File> &files);

void show_files(std::vector<File> &files, const Flags &flags);

bool parse_out(const File &file, const Flags &flags);

void show(const std::string &directory_name);

std::string get_dir_to_walk(int argc, char *argv[]);


#endif //LAB1_FUNCTIONS_H
