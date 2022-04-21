#include <stdlib.h>
#include <io.h>

struct queue
{
    char *data;
    struct queue *next;
};

void sort(struct queue **head)
{
    struct queue *current, *elementToSwap, *prevElementToSwap, *prevFormCur;

    // В очереди это бы выглядело так (не в первой итерации цикла):
    //      1            2               3                  2           8           9          5           3...
    //      /\           /\              /\                 /\
    //  prevFromCur    current    prevElementToSwap      elementToSwap

    prevFormCur = (struct queue *)malloc(sizeof(struct queue));

    if(!*head)
        return;

    current = prevElementToSwap = *head;
    // s - elementToSwap;
    // p - prevFromCur;
    // pr - prevNexFromCur

    while(current->next)
    {
        elementToSwap = current->next;
        prevElementToSwap = current;
        while(elementToSwap)
        {
            if(strcmp(current->data, elementToSwap->data) <= 0) {
                prevElementToSwap = elementToSwap;
                elementToSwap = elementToSwap->next;
            }
            else
            {
                if(current == *head)                                 // Если текущий элемент больше следующего,
                {                                                    // и является головой (началом) списка
                    *head = elementToSwap;                           // голова становится большим элементом
                    prevElementToSwap->next = current->next;         // предыдущий большего элемента указывает на следующий большего
                    elementToSwap->next = current;                   // следующий псле переставленного большего - текущий
                }
                else                                                 // Если текущий элемент больше элемента, с которым
                {                                                    // сравниваем и не является головой очереди, то:
                    prevFormCur->next = elementToSwap;               // указываем что предыдущий от текущего указывает на больший элемент
                    prevElementToSwap->next = elementToSwap->next;   // предыдущий от большего указывает на следующий от большего
                    elementToSwap->next = current;                   // следующий после переставленного большего - текущий
                }
            }
        }
        prevFormCur = current;
        current = current->next;
    }

}

//for(; current->next; current = current->next)
//{
//for(nextFromCur = current->next; elementToSwap; elementToSwap = elementToSwap->next, prevElementToSwap = prevElementToSwap->next)
//{
//if(nextFromCur == current->next)
//prevElementToSwap = current;
//if(strcmp(current->data, elementToSwap->data) > 0)
//{
//prevElementToSwap->next = elementToSwap->next;
//nextFromCur->next = current;
//prevFormCur->next = prevElementToSwap;
//current = elementToSwap;
//}
//}
//if(!newHead)
//{
//newHead = current;
//free(prevFormCur);
//}
//prevFormCur = current;
//}