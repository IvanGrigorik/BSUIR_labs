//
// Created by sifi on 24.03.2022.
//

#include "parent_functions.h"

void menu() {
    printf("'+' - creat new process\n");
    printf("'-' - delete last created process\n");
    printf("'k' - kill all process\n");
    printf("'g' - allows all process send statistic; also can specify one pid: g <num>'\n");
    printf("'s' - forbid  process to send statistic; also can specify one pid: s <num>'\n");
    printf("'p' <num> - ask <num> process to send his own statistic\n");
    printf("'q' - end program\n");
}

void add_new_process(processes_info **proc_list, int *pid_count) {
    pid_t temp = fork();

    if (temp < 0) {
        some_error(__LINE__, __FILE__, "Fork");
    } else if (temp != 0) {
        // Parent process
        (*pid_count)++;
        *proc_list = (processes_info *) realloc(*proc_list, *(pid_count) * sizeof(processes_info));
        if (!(*proc_list)) {
            some_error(__LINE__, __FILE__, "Allocation");
        }
        (*proc_list)[(*pid_count) - 1].is_allowed = true;
        (*proc_list)[(*pid_count) - 1].pid = temp;

        printf("%d process with PID %d was created\n", (*pid_count), temp);
    } else {
        // Child process
        char argv[5];
        sprintf(argv, "C_%d", (*pid_count));
        execl("/home/sifi/BSUIR_labs/4_term/SPO/lab4/child/cmake-build-debug/child", argv, NULL);
    }
}

void kill_last_proc(processes_info **proc_list, int *pid_count) {
    int temp;
    union sigval sig_value;
    sig_value.sival_int = 0;

    temp = sigqueue((*proc_list)[*pid_count - 1].pid, SIGUSR1, sig_value);
    if (temp != 0) {
        some_error(__LINE__, __FILE__, "kill");
    } else {
        wait(&temp);
        printf("process %d with PID %d was killed\n", (*pid_count), (*proc_list)[(*pid_count) - 1].pid);
    }

    (*pid_count)--;
    *proc_list = (processes_info *) realloc(*proc_list, *(pid_count) * sizeof(processes_info));
}

void kill_all_processes(processes_info **proc_list, int *pid_count) {
    int temp;
    union sigval sig_value;
    sig_value.sival_int = 0;

    for (int i = 0; i < (*pid_count); i++) {
        temp = sigqueue((*proc_list)[i].pid, SIGUSR1, sig_value);

        if (temp != 0) {
            some_error(__LINE__, __FILE__, "kill");
        } else {
            wait(&temp);
            printf("process %d with PID %d was killed\n", i + 1, (*proc_list)[i].pid);
        }
    }
    (*pid_count) = 0;

    free(*proc_list);
    *proc_list = (processes_info *) malloc(sizeof(processes_info));
}

void some_error(int line, char *file, char *error) {
    printf("Error in line %d of file %s\n", line, file);
    perror(error);
    exit(EXIT_FAILURE);
}

int parse(char *p) {
    while (*p) {
        if (isdigit(*p)) {
            return strtol(p, &p, 10);
        } else {
            p++;
        }
    }
    return -1;
}


extern int pid_count;
extern processes_info *processes_list;

void parent_handler(__attribute__((unused)) int sig_number, siginfo_t *sig_info, __attribute__((unused)) void *none) {
    union sigval sig_value;

    if (sig_info->si_int == 0) {
        for (int i = 0; i <= pid_count; i++) {
            if (processes_list[i].pid == sig_info->si_pid && processes_list[i].is_allowed) {
                sig_value.sival_int = 2;
                sigqueue(sig_info->si_pid, SIGUSR1, sig_value);
            } else if (processes_list[i].pid == sig_info->si_pid && !(processes_list[i].is_allowed)) {
                sig_value.sival_int = 1;
                sigqueue(sig_info->si_pid, SIGUSR1, sig_value);
            }
        }
    }
}

void refresh_mef_refresh(__attribute__((unused)) int signum){
    for(int i = 0; i < pid_count; i++){
        processes_list[i].is_allowed = true;
    }
}