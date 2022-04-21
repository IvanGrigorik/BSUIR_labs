#include <stdio.h>
#include <stdlib.h>
#include <io.h>

// Бинарное дерево записать в файл,
// имя которого вводится с командной строки

typedef struct tree
{
    char *info;
    struct tree *left;
    struct tree *right;
}tree;

void putTreeInToFile(FILE *f, tree *node);

int main(int argc, char *argv[])
{
    if(argc != 2)
        return 1;
    char *fileName;
    fileName = strcat(argv[1], ".txt");

    FILE *f = fopen(fileName, "w+");

    struct tree *root = NULL;
    putTreeInToFile(f, root);
}

// Запишем нерекурсивно. Просто потому что можем.
typedef struct stack
{
    tree *node;
    struct stack *next;
}stack;

// Push - это заталкивание записи в стек
void stackPush(stack **head, tree *node)
{
    stack *newHead;
    newHead = (stack *)malloc(sizeof (stack));

    newHead->node = node;
    newHead->next = *head;
    *head = newHead;
}

// Pop - это выскакивание последней записи из стека
// Возвращаемся на предыдущий узел в дереве
tree* stackPop(stack **head)
{
    if(*head == NULL)
        return NULL;

    stack *prevHead;
    tree *node = NULL;


    prevHead = *head;           // Переставляем голову
    *head = (*head)->next;      // на следующую
    node = prevHead->node;      // Возвращаемый элемент - предыдущий узел
    free(prevHead);             // Очищаем предыдущую голову

    return node;                // Возвращаем предыдущий узел
}

void putTreeInToFile(FILE *f, tree *node)
{
    stack *newStack = NULL;

    while(node || newStack)
    {
        // Если узел существует (т.е. прошлым переходом не перешли вникуда)
        // то переходим налево (может и вникуда, но тогда)...
        if(node)
        {
            stackPush(&newStack, node);
            node = node->left;
        }
        // .. но тогда) если перешли вникуда
        // то возвращаемся на предыдущий узел, и переходим вправо
        else
        {
            node = stackPop(&newStack);
            fprintf(f, "%s ", node->info);
            node = node->right;
        }
    }
}