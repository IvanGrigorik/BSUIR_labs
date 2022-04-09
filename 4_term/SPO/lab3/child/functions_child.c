//
// Created by sifi on 24.03.2022.
//

#include "functions_child.h"

extern statistic stats;

void child_handler(__attribute__((unused)) int sig_number, siginfo_t *sig_info, __attribute__((unused)) void *none) {
    // 0 - flag to kill process
    if (sig_info->si_int == 0) {
        exit(EXIT_SUCCESS);
    }

    // 1 - flag to disable all processes out statistic
    // 2 - flag to allow all processes out statistic
    if (sig_info->si_int == 1) {
        stats.is_allowed = false;
    }

    if (sig_info->si_int == 2) {
        stats.is_allowed = true;
    }
}

void collect_stats(__attribute__((unused)) int signum) {
    if (stats.nums.num1 == 0 && stats.nums.num2 == 0) {
        ++stats.collected_numbers[0];
    } else if (stats.nums.num1 == 0 && stats.nums.num2 == 1) {
        ++stats.collected_numbers[1];
    } else if (stats.nums.num1 == 1 && stats.nums.num2 == 0) {
        ++stats.collected_numbers[2];
    } else if (stats.nums.num1 == 1 && stats.nums.num2 == 1) {
        ++stats.collected_numbers[3];
    }
    stats.cycles++;
}

void output_stats() {
    if (stats.is_allowed == true) {
        printf("PID: %d; PPID: %d; Statistic: ", getpid(), getppid());
        printf("{ ");
        for (int i = 0; i < 4; i++) {
            printf("%d ", stats.collected_numbers[i]);
        }
        printf("}\n");
    }
    stats.cycles = 0;
}

void request_for_parent() {
    union sigval sig_value;
    sig_value.sival_int = 0;

    int temp = sigqueue(getppid(), SIGUSR1, sig_value);

    if (temp != 0) {
        printf("Some errors in %d", getpid());
    }

}