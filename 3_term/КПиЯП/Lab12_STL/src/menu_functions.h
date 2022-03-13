/*
 * Created by Ivan on 29.11.2021.
 * BSUiR, 2021
 */

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>


// Filenames.
constexpr char source_filename[] = "source.txt";
constexpr char target_filename[] = "target.txt";


int get_menu_choice();

int get_int(int min_size, int max_size);

void add_new_string(std::ofstream &source, bool is_first);

void show_source(std::ifstream &source);

void show_target(std::ifstream &target);

void search_without(std::ifstream &source);

void search_with(std::ifstream &source);

void delete_duplicated(std::ifstream &source);