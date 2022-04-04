//
// Created by sifi on 28.03.2022.
//

#ifndef SPO_COURSEWORK_FUNCTIONS_H
#define SPO_COURSEWORK_FUNCTIONS_H

#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <dirent.h>
#include <cstring>

#include <openssl/md5.h>
#include <map>
#include <utility>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <csignal>

typedef struct file_data_t {
    std::string file_name{};
    std::string file_hash{};

    file_data_t(std::string fileName, std::string fileHash) {
        file_name = std::move(fileName);
        file_hash = std::move(fileHash);
    }
} file_data_t;

typedef struct file_to_delete {
    std::string file_name{};
    std::string file_path{};

    file_to_delete(std::string fileName, std::string filePath) {
        file_name = std::move(fileName);
        file_path = std::move(filePath);
    }
} file_to_delete_t;

void collect_files(const std::string &current_dir,
                   std::vector<file_data_t> &unique_files,
                   std::vector<file_to_delete_t> &duplicated_files, char flag);

unsigned long get_size_by_fd(int fd);

void parent_handler(__attribute__((unused)) int sig_number, siginfo_t *sig_info, __attribute__((unused)) void *none);

#endif //SPO_COURSEWORK_FUNCTIONS_H
