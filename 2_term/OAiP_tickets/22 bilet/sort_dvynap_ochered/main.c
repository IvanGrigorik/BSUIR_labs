#include <stdio.h>
#include <io.h>

// Сортировка двунаправленной очереди через указатели
// head "снизу", список "очередь" начинается с хвоста

typedef struct queue
{
    char someInfo[];
    struct queue *next;
    struct queue *prev;
}queue;

/*
void sort(queue **tail, queue **head)
{
    queue *tempHead, *tempTail, *swapElement;

    for(tempHead = *head; tempHead; tempHead = tempHead->prev)
    {
        for(tempTail = *tail; tempTail; tempTail = tempTail->next)
        {
            // Если следующий элемент меньше, чем предыдущий
            if(strcmp(tempTail->next->someInfo, tempTail->someInfo) < 0)
            {
                // Устанавливаем временный указатель на элемент, который надо переставить
                swapElement = tempTail->next;

                // Если сортируемый элемент - хвост
                if(!tempTail->prev)
                    *tail = tempTail->next;

                tempTail->next = tempTail->next->next;

                // Если у сортируемого элемента если послеследующий элемент
                if(tempTail->next)
                    tempTail->next->prev = tempTail;
                else
                    tempHead = *head = tempTail;

                swapElement->prev = tempTail->prev;
                swapElement->next = tempTail;

                if(swapElement->prev)
                    swapElement->prev->next = swapElement;
                tempTail->prev = swapElement;

                // Откат элемента для for-a, потому что могут стоят несколько меньших подряд
                tempTail = tempTail->prev;
            }
        }
    }
}*/

void sort(queue **head, queue **tail)
{
    queue *tempHead, *tempTail, *swapElement;

    for(tempHead = *head; tempHead; tempHead = tempHead->prev)
        for(tempTail = *tail; tempTail; tempTail = tempTail->next)
            if(strcmp(tempTail->someInfo, tempTail->next->someInfo) > 0)
            {
                swapElement = tempTail->next;

                if(tempTail == *tail)
                    *tail = tempTail->next;

                tempTail->next = tempTail->next->next;

                if(tempTail->next)
                    tempTail->next->prev = tempTail;
                else
                    tempHead = *head = tempTail;

                swapElement->next = tempTail;
                swapElement->prev = tempTail->prev;
                if(swapElement->prev)
                    swapElement->prev->next = swapElement;
                tempTail->prev = swapElement;

                tempTail = tempTail->prev;
            }
}
