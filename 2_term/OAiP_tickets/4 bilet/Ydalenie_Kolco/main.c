#include <stdio.h>
#include <stdlib.h>
struct circle *delete(struct circle *newCircle);
struct circle
{
    int info;
    struct circle *next, *previous;
};

int main()
{
    struct circle *newCircle = NULL;


    newCircle = (struct circle *)malloc(sizeof(struct circle));
    newCircle->previous = newCircle;
    newCircle->next = newCircle;
    newCircle->info = 123;
    newCircle = delete(newCircle);
}

struct circle *delete(struct circle *newCircle)
{
    int infoToDelete;
    scanf("%d", &infoToDelete);

    if(!newCircle)
        return NULL;

    struct circle *enterDot = newCircle;

    do
    {
        if(enterDot->info != infoToDelete)
            newCircle = enterDot->next;
        else
        {
            if(enterDot->previous == newCircle)
                free(enterDot);

            else
            {
                enterDot->previous->next = enterDot->next;
                enterDot->next->previous = enterDot->previous;
                free(enterDot);
                return newCircle;
            }
        }

    }while(newCircle != enterDot);

    puts("There no such element");
    return newCircle;
}