#include <stdio.h>
#include <stdlib.h>
#include <io.h>

// Удаление элемета из однонаправленной очереди

typedef struct queue
{
    char *info;
    struct queue *next;
}queue;

void delete(queue **head, char *elementToDelete)
{
    struct queue *runner, *temp;

    if((strcmp((*head)->info, elementToDelete) == 0) && (*head)->next)
    {
        temp = (*head);
        *head = (*head)->next;
        free(temp);
        return;
    }
    else if((strcmp((*head)->info, elementToDelete) == 0) && (*head)->next == NULL)
    {
        free(*head);
        return;
    }
    runner = *head;

    while(runner->next)
    {
        if(strcmp(runner->next->info, elementToDelete) == 0)
        {
            if(runner->next->next)
            {
                temp = runner;
                runner->next = runner->next->next;
                free(temp);
            }
            else
            {
                temp = runner->next;
                free(temp);
                runner->next = NULL;
                return;
            }
        }
        runner = runner->next;
    }
}