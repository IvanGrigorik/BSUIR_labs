//
// Created by sifi on 13.04.2022.
//

#ifndef MAIN_FUNCTIONS_H
#define MAIN_FUNCTIONS_H

#include <semaphore.h>
#include <fcntl.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

sem_t * open_sem(sem_t *semaphore, char* sem_name, int oflag, mode_t mode, unsigned int value);

#endif //MAIN_FUNCTIONS_H
