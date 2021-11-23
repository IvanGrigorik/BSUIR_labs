/*
 * Created by Ivan on 23.11.2021.
 * BSUiR, 2021
 */

#pragma once

#include <iostream>
#include "file_work.h"

int get_menu_choice();

int get_int(int min_size, int max_size);

void add_file(std::ofstream &file, const std::string &file_type);

void search_file(std::ifstream &file, const std::string &file_type);

void delete_file_func(std::ifstream &file, const std::string &file_type);

;