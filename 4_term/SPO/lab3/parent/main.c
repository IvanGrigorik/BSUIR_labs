#include <sys/time.h>
#include "parent_functions.h"


processes_info *processes_list;
int pid_count = 0;

int main() {
    char numbers[10];
    int choice;

    processes_list = (processes_info *) malloc(sizeof(processes_info));
    menu();

    struct sigaction parent_action;
    parent_action.sa_flags = SA_SIGINFO;
    parent_action.sa_sigaction = parent_handler;
    sigaction(SIGUSR1, &parent_action, NULL);

    // Timer busy
    signal(SIGALRM, refresh_mef_refresh);
    struct itimerval delay;

    delay.it_value.tv_sec = 8;
    delay.it_value.tv_usec = 0;
    delay.it_interval.tv_sec = 0;
    delay.it_interval.tv_usec = 0;

    while (1) {
        choice = getchar();

        switch (choice) {

            case '+': {
                add_new_process(&processes_list, &pid_count);
                break;
            }

            case '-': {
                kill_last_proc(&processes_list, &pid_count);
                break;
            }

            case 'k': {
                kill_all_processes(&processes_list, &pid_count);
                break;
            }

            case 's': {
                fgets(numbers, 10, stdin);
                int num = parse(numbers);

                if (num <= 0) {
                    for (int i = 0; i < pid_count; i++) {
                        processes_list[i].is_allowed = false;
                    }
                } else if (num > pid_count) {
                    some_error(__LINE__, __FILE__, "PID count");
                    break;
                } else {
                    processes_list[num - 1].is_allowed = false;
                }

                break;
            }

            case 'g': {
                fgets(numbers, 10, stdin);
                int num = parse(numbers);

                if (num <= 0) {
                    for (int i = 0; i < pid_count; i++) {
                        processes_list[i].is_allowed = true;
                    }
                    break;
                } else if (num > pid_count) {
                    some_error(__LINE__, __FILE__, "PID count");
                    break;
                } else {
                    processes_list[num - 1].is_allowed = true;
                }
                break;
            }

            case 'p': {
                fgets(numbers, 10, stdin);
                int num = parse(numbers);

                if (num <= 0 || num > pid_count) {
                    break;
                }

                for (int i = 0; i < pid_count; i++) {
                    if (i == num - 1) {
                        processes_list[i].is_allowed = true;
                        continue;
                    }
                    processes_list[i].is_allowed = false;
                }

                int ret = setitimer(ITIMER_REAL, &delay, NULL);
                if (ret) {
                    perror("timer");
                    exit(EXIT_FAILURE);
                }

                break;
            }

            case 'q': {
                kill_all_processes(&processes_list, &pid_count);
                exit(EXIT_SUCCESS);
            }

            default:
                break;
        }
    }
}
