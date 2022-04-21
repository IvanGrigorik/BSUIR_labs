#include <stdio.h>
#include <stdlib.h>

typedef struct tree
{
    int data;
    struct tree *left;
    struct tree *right;
}tree;

void add(tree **treePtr)
{
    int valueToAdd;
    scanf("%d", &valueToAdd);

    while(*treePtr)
    {
        if((*treePtr)->data == valueToAdd)
            return;

        if((*treePtr)->data > valueToAdd)
            treePtr = &(*treePtr)->left;
        else
            treePtr = &(*treePtr)->right;
    }

    *treePtr = (tree *)malloc(sizeof(tree));
    (*treePtr)->data = valueToAdd;
    (*treePtr)->left = (*treePtr)->right = NULL;
    return;
}
