//
// Created by sifi on 13.04.2022.
//

#ifndef MAIN_CIRCLE_H
#define MAIN_CIRCLE_H

// For work with threads sync
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// For NULL
#include <stddef.h>
// for rand()
#include <stdlib.h>
#include <stdbool.h>

typedef struct message {
    char type;
    unsigned int hash;
    int size;
    char data[256];
    bool is_filled;
} message_t;

typedef struct circle {
    message_t message[10];
    // we can have 10 messages with 256-bytes data, where:
    // message[i][0] - message type
    // message[i][1]/[2] - message hash
    // message[i][3] - message length
    // message[i][4 - 254] - message data

    short added;
    short deleted;
    int head;
    int tail;
} circle_t;

#endif //MAIN_CIRCLE_H
