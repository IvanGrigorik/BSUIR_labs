//
// Created by Ivan on 23.04.2021.
//

#ifndef LAB5_FUN_H
#define LAB5_FUN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union information
{
    char date[9];
    int duration;
};

struct tour
{
    union information info;
    int cost;
    char *name;
    int indicator;
};

struct queue
{
    struct tour data;
    struct queue *next;
};

int menu();
int check();
char *getString(void);
int getDigits(struct queue *tourList);
void addElement(struct queue **head, struct queue **tail);
int emptyCheck(struct queue *head);
void clear(struct queue **head, struct queue **tail);

int findMax(struct queue *toursList, int code);
char *MyItoA(int num);
void spacePrint(int i);
void outputOne(struct queue *tour, int i, int sizeName);
void outputHead(struct queue *toursList);
void output(struct queue *tourList);

void uppercase(char *find);
void search(struct queue *toursList);

void delete(struct queue **head, struct queue **tail);

char *getFileName(int code);
void savingFile(struct queue *head);

void inputFromFile(struct queue **head, struct queue **tail);


#endif //LAB5_FUN_H
