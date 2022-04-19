//
// Created by sifi on 24.03.2022.
//

#ifndef CHILD_FUNCTIONS_CHILD_H
#define CHILD_FUNCTIONS_CHILD_H

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

void child_handler(__attribute__((unused)) int sig_number, siginfo_t *sig_info, __attribute__((unused)) void *none);


typedef struct numbers {
    int num1;
    int num2;
} data;

typedef struct statistic {
    pid_t pid;
    pid_t ppid;

    data nums;

    int collected_numbers[4];

    bool is_allowed;
    int cycles;
} statistic;

void collect_stats(__attribute__((unused)) int signum);

void output_stats();

void request_for_parent();
#endif //CHILD_FUNCTIONS_CHILD_H
