//
// Created by sifi on 14.04.2022.
//

#ifndef LAB8_CIRCLE_H
#define LAB8_CIRCLE_H

// for rand()
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

typedef struct message {
    char type;
    unsigned int hash;
    int size;
    char data[256];
    bool is_filled;
} message_t;

typedef struct circle {
    message_t message[10];
    short added;
    short deleted;
    int head;
    int tail;
} circle_t;

#endif //LAB8_CIRCLE_H
