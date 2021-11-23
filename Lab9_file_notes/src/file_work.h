//
// Created by Ivan on 15.11.2021.
//

#pragma once

#include "Notes.h"

constexpr char text[] = "text.txt";
constexpr char binary[] = "binary.bin";

void print_text(std::ifstream &file);

void reverse_print_text(std::ifstream &file);

void print_binary(std::ifstream &file);

void reverse_print_binary(std::ifstream &file);

void new_files(std::ofstream &file);

void file_searching(const std::string &file_type, std::ifstream &file,
                    const std::string &note_info_to_find, int field_to_find);

void file_delete(const std::string &file_type, std::ifstream &file, int delete_number);

void delete_duplicated();