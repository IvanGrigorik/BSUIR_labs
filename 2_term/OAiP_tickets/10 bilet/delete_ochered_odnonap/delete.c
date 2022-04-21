#include <stdio.h>
#include <io.h>
#include <stdlib.h>

// Удалить любой элемент из однонаправленной очереди

typedef struct queue
{
    char *data;
    struct queue *next;
}queue;

void delete(queue **tail, char *dataToDelete);

int main()
{
    queue *tail;
    char delElement[30];
    gets(delElement);
    delete(&tail, delElement);
}

void delete(queue **tail, char *dataToDelete)
{
    queue *runner = *tail, *temp;
    
    if (strcmp((*tail)->data, dataToDelete) == 0)
    {
        free(*tail);
        *tail = runner->next;
    }
    while (runner->next != NULL)
    {
        if (strcmp(runner->next->data, dataToDelete) == 0)
        {
            if (runner->next->next == NULL)
                free(runner->next);
            else
            {
                temp = runner->next;
                runner->next = runner->next->next;
                free(temp);
            }
        }
        runner = runner->next;
    }
}