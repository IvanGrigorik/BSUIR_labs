//
// Created by sifi on 13.04.2022.
//

#include <stdlib.h>
#include "functions.h"

sem_t *open_sem(sem_t *semaphore, char *sem_name, int oflag, mode_t mode, unsigned int value) {
    if ((semaphore = sem_open(sem_name, oflag, mode, value)) == SEM_FAILED) {
        perror("Semaphore open error: ");
        exit(EXIT_FAILURE);
    }
    return semaphore;
}