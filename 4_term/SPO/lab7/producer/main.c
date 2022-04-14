#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

#include "../circle.h"
#include "../functions.h"

bool is_alive = true;

//lose_lose
int hashing(char *str) {
    unsigned int hash;

    char c;

    while (c = *str++) {
        hash += c;
    }

    return hash;
}

void kill_func(__attribute__((unused)) int sig_number) {
    is_alive = false;
}

int main(int argc, char *argv[]) {
    struct sigaction kill_handler;
    kill_handler.sa_handler = kill_func;

    int shmid = atoi(*argv);
    circle_t *msg_circle = shmat(shmid, NULL, 0);

    sem_t *producer_sem = sem_open("producer_sem", 0);
    sem_t *mutex_ = sem_open("mutex_", 0);

    if (producer_sem == SEM_FAILED || mutex_ == SEM_FAILED) {
        perror("Semaphore open error: ");
        exit(EXIT_FAILURE);
    }
    time_t time1;
    srand((unsigned) time(&time1));
    int new_size;

    while (is_alive) {
        sem_wait(producer_sem);
        sem_wait(mutex_);

        if (!msg_circle->message[msg_circle->head].is_filled) {
            printf(YELLOW "NEW MESSAGE NUMBER %d SENT" WHITE "\n" , msg_circle->head);
            new_size = rand() % 80;
            for (int i = 0; i < new_size; i++) {
                msg_circle->message[msg_circle->head].data[i] = 49 + (rand() % 72);
            }
            msg_circle->message[msg_circle->head].size = new_size;
            msg_circle->message[msg_circle->head].is_filled = true;
            msg_circle->message[msg_circle->head].hash = hashing(msg_circle->message[msg_circle->head].data);
            msg_circle->added++;
            if (msg_circle->head == 9) {
                msg_circle->head = 0;
            } else {
                msg_circle->head++;
            }
        } else {
            printf(RED "Queue is full" WHITE "\n");
        }

        sem_post(producer_sem);
        sem_post(mutex_);

        sleep(1);
    }

    sem_close(producer_sem);
    sem_close(mutex_);
    shmdt(msg_circle);
    exit(EXIT_SUCCESS);
}
