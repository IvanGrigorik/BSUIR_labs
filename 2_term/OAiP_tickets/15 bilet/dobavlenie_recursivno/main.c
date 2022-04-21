#include <stdio.h>
#include <stdlib.h>
#include <io.h>

// Написать функцию для добавления элемента дерева рекурсивно

typedef struct tree
{
    char *lastName;
    int year;
    struct tree *left;
    struct tree *right;
}tree;

void add(tree **node, char *newLastName, int newYear)
{
    if(!*node)
    {
        *node = (struct tree *)malloc(sizeof(tree));
        (*node)->lastName = newLastName;
        (*node)->year = newYear;
        (*node)->left = (*node)->right = NULL;
    }
    else if(strcmp((*node)->lastName, newLastName) == 0)
        return;
    else if(strcmp((*node)->lastName, newLastName) > 0)
        add(&((*node)->left), newLastName, newYear);
    else
        add(&((*node)->right), newLastName, newYear);
}