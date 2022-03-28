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
#include <vector>
#include <sstream>


void collect_files(const std::string &current_dir, std::map<std::string, std::string> & files_map);

unsigned long get_size_by_fd(int fd);

#endif //SPO_COURSEWORK_FUNCTIONS_H
