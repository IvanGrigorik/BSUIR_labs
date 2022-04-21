#include <stdlib.h>
#include <io.h>

typedef struct ring
{
    char *data;
    struct ring *next;
}ring;

void del(ring **head, char *dataToDel)
{
    if(*head == NULL)
        return;

    ring *runner, *temp;

    runner = *head;

    if ((strcmp((*head)->data, dataToDel) == 0) && (*head)->next == *head) {
        free(*head);
        *head = NULL;
        return;
    }

    while(runner->next != *head)
    {
        if(strcmp(runner->next->data, dataToDel) == 0)
        {
            temp = runner->next;
            runner->next = runner->next->next;
            free(temp);
        }
        runner = runner->next;
    }
}
