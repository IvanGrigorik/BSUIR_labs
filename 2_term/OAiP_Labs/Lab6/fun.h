//
// Created by Ivan on 20.05.2021.
//

#ifndef LAB6_CBP_FUN_H
#define LAB6_CBP_FUN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARRAY_SIZE 20

struct information
{
    char englishWord[ARRAY_SIZE];
    char russianWord[ARRAY_SIZE];
};

struct tree
{
    struct information element;
    struct tree *left;
    struct tree *right;
};

int menu();
void insert(struct tree **head, struct information value);
struct tree *getMemory(struct information value);
void input(struct tree **head);
void show(struct tree *obitoRoot);
void deleteAll(struct tree **root);
void delete(struct tree **node);
void showTreeByStack(struct tree *node);
void print(struct tree* root, int level);
struct tree *balance (struct tree *temp);

#endif //LAB6_FUN_H
