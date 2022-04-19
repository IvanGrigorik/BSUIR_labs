//
// Created by sifi on 04.03.2022.
//

#ifndef MAIN_C_FUNCTIONS_H
#define MAIN_C_FUNCTIONS_H

#define ANSI_COLOR_CYAN "\033[0;34m"
#define ANSI_COLOR_RESET "\x1b[0m"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void show_env(char *env[]);

char** get_child_env(char* env_file_path);

char* get_child_path(char** environments);

#endif //MAIN_C_FUNCTIONS_H
