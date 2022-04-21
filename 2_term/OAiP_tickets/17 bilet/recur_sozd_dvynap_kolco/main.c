#include <stdio.h>
#include <stdlib.h>

// Рекурсивно создать двунаправленное кольцо

typedef struct ring
{
    char info[20];
    struct ring *right;
    struct ring *left;
}ring;

void add(ring **enter, int much);

int main()
{
    ring *newRing = NULL;
    int much;

    scanf("%d", &much);
    add(&newRing, --much);

    return 0;
}

void add(ring **enter, int much)
{
    if(*enter == NULL)
    {
        *enter = (ring *)malloc(sizeof(ring));
        (*enter)->left = (*enter)->right = *enter;
        scanf("%s", (*enter)->info);
        if(much != 0)
            add(enter, --much);
    }
    else
    {
        ring *newElement;
        newElement = (ring *)malloc(sizeof(ring));

        newElement->right = (*enter)->right;
        (*enter)->right = newElement;
        (*enter)->right->left = newElement;
        newElement->left = (*enter);

        scanf("%s", newElement->info);
        if(much != 0)
            add(enter, --much);
    }
}