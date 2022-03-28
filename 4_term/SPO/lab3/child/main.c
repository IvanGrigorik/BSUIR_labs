#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include "functions_child.h"

statistic stats;

static const data ones = {1, 1};
static const data zeros = {0, 0};

int main() {
    struct sigaction child_action;
    child_action.sa_flags = SA_SIGINFO;
    child_action.sa_sigaction = child_handler;
    sigaction(SIGUSR1, &child_action, NULL);

    // Timer work
    signal(SIGALRM, collect_stats);
    struct itimerval delay;

    delay.it_value.tv_sec = 0;
    delay.it_value.tv_usec = 50000;
    delay.it_interval.tv_sec = 0;
    delay.it_interval.tv_usec = 50000;

    int ret = setitimer(ITIMER_REAL, &delay, NULL);
    if (ret) {
        perror("timer");
        exit(EXIT_FAILURE);
    }

    // Main loop
    while (1) {
        stats.nums = ones;
        stats.nums = zeros;

        if (stats.cycles >= 101) {
            request_for_parent();
            // Wait while parent send request answer
            usleep(500);
            output_stats();
        }
    }
}
