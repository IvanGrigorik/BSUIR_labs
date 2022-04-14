#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

#include "../functions.h"
#include "../circle.h"

bool is_alive = true;

void kill_func(__attribute__((unused)) int sig_number) {
    is_alive = false;
}

int main(int argc, char *argv[]) {
    struct sigaction kill_handler;
    kill_handler.sa_handler = kill_func;

    int shm_id = atoi(*argv);
    circle_t *msg_circle = shmat(shm_id, NULL, 0);


    sem_t *consumer_sem = sem_open("consumer_sem", 0);
    sem_t *mutex_ = sem_open("mutex_", 1);

    if (consumer_sem == SEM_FAILED || mutex_ == SEM_FAILED) {
        perror("Semaphore open error: ");
        exit(EXIT_FAILURE);
    }

    char message_to_out[256];

    while (is_alive) {
        sem_wait(consumer_sem);
        sem_wait(mutex_);

        if (msg_circle->message[msg_circle->tail].is_filled) {
            strcpy(message_to_out, msg_circle->message[msg_circle->tail].data);
            msg_circle->deleted++;
            printf(CYAN "Received message number %d: %s\n", msg_circle->deleted, message_to_out);
            printf("Message hash: %d\n", msg_circle->message[msg_circle->tail].hash);
            printf("Message size: %d" WHITE "\n", msg_circle->message[msg_circle->tail].size);
            msg_circle->message[msg_circle->tail].is_filled = false;
            if (msg_circle->tail == 9) {
                msg_circle->tail = 0;
            } else {
                msg_circle->tail++;
            }

            printf("\nStats:\nTotal added: %d\nTotal received: %d\n\n", msg_circle->added, msg_circle->deleted);
        } else {
            printf(RED "Queue is empty!" WHITE "\n");
        }

        sem_post(consumer_sem);
        sem_post(mutex_);

        sleep(1);
    }


    shmdt(msg_circle);
    exit(EXIT_SUCCESS);
}