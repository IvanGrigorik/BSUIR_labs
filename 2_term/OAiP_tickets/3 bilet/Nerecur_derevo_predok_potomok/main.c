#include <stdio.h>
#include <stdlib.h>
// Просмотр дерева нерекурсивно.
// Сначала печатается предок, а потом потомок

typedef struct tree
{
    int info;
    struct tree *left;
    struct tree *right;
}tree;

typedef struct stack
{
    tree *node;
    struct stack *next;
}stack;

// Функция заталкивания в стек
void push(stack **head, tree *node)
{
    stack *newHead;
    newHead = (stack *)malloc(sizeof(stack));
    newHead->node = node;
    newHead->next = *head;
    *head = newHead;
}

// Выталкивание последнего элемента из стека
tree *pop(stack **head)
{
    tree *node;
    stack *prevHead;

    prevHead = *head;
    node  = prevHead->node;
    *head = (*head)->next;
    free(prevHead);
    return node;
}

void show(tree *node)
{
    if(node == NULL)
        return;
    stack *newStack = NULL;

    while(newStack || node)
    {
        if(node)
        {
            push(&newStack, node);
            node = node->left;
        }
        else
        {
            node = pop(&newStack);
            printf("%d", node->info);
            node = node->right;
        }
    }
}