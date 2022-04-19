//
// Created by sifi on 24.03.2022.
//

#ifndef PARENT_PARENT_FUNCTIONS_H
#define PARENT_PARENT_FUNCTIONS_H

#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <malloc.h>
#include <stdlib.h>
#include <wait.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct processes_info{
    pid_t pid;
    bool is_allowed;
}processes_info;

void menu();

void kill_all_processes(processes_info **proc_list, int *pid_count) ;

void add_new_process(processes_info **proc_list, int *pid_count);

void kill_last_proc(processes_info **proc_list, int *pid_count);

void some_error(int line, char* file, char* error);

void parent_handler(__attribute__((unused)) int sig_number, siginfo_t *sig_info, __attribute__((unused)) void *none);

int parse(char *p);

void refresh_mef_refresh(__attribute__((unused)) int signum);

#endif //PARENT_PARENT_FUNCTIONS_H