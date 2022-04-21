#include <stdlib.h>
#include <io.h>

typedef struct stack
{
    int data;
    struct stack *next;
}stack;

typedef struct ring
{
    char *data;
    struct stack *stackPtr;
    struct ring *next;
}ring;

void del (ring **enter)
{
    ring *runner, *maxElement, *preMaxElement;
    stack *tempHead;

    runner = *enter;
    maxElement = *enter;

    if ((*enter)->next == *enter)
    {
        free(*enter);
        return;
    }

    while (runner->next != *enter)
    {
        if (strcmp(runner->next->data, maxElement->data) > 0)
        {
            preMaxElement = runner;
            maxElement = runner->next;
        }
        runner = runner->next;
    }

    if(maxElement == *enter)
    {
        while((*enter)->stackPtr)
        {
            tempHead = (stack *)malloc(sizeof(struct stack));           // Распределяю память на новую голову стека
            tempHead->data = (*enter)->stackPtr->data;                  // Копирую данные из стека, который надо переписать в новую голову

            tempHead->next = (*enter)->next->stackPtr;                  // Показываю, что следующий элемент новой головы - предыдущая голова стека
            (*enter)->next->stackPtr = tempHead;                        // Устанавливаю новую голову

            (*enter)->stackPtr = (*enter)->stackPtr->next;
        }
        runner->next = (*enter)->next;
        free(*enter);
    }
    else
    {
        while(maxElement->stackPtr)
        {
            tempHead = (stack *)malloc(sizeof(struct stack));
            tempHead->data = maxElement->stackPtr->data;

            tempHead->next = maxElement->next->stackPtr;
            maxElement->next->stackPtr = tempHead;

            maxElement->stackPtr = maxElement->stackPtr->next;
        }

        preMaxElement->next = maxElement->next;
        free(maxElement);
    }
}
