#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED
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

struct stack
{
    struct tour data;
    struct stack *next;
};

void search(struct stack *tourList);
int menu();
int check();
void addElement(struct stack **head);
char *getString(void);
void output(struct stack *head);
int getDigits(struct stack *element);
int findmax (struct stack *toursList, int code);
char *MyItoA(int num);
void spacePrint(int i);
void outputHead(struct stack *toursList);
void uppercase(char *find);
void outputOne(struct stack *tour, int i, int sizeName);
void delete(struct stack **toursList);
void saveFileElement(struct stack **toursList, FILE *binaryFile, FILE *textFile);
void inputFromFile(struct stack **toursList, FILE *binaryFile, FILE *textFile);
char *getFileName(int code);
void reverseStack(struct stack **head);

#endif // HEAD_H_INCLUDED
