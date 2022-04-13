//
// Created by sifi on 13.04.2022.
//

#ifndef MAIN_FUNCTIONS_H
#define MAIN_FUNCTIONS_H

#include <semaphore.h>
#include <fcntl.h>
#include <stdio.h>

sem_t * open_sem(sem_t *semaphore, char* sem_name, int oflag, mode_t mode, unsigned int value);

#endif //MAIN_FUNCTIONS_H
