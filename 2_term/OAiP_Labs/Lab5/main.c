#include "fun.h"

int main()
{
    struct queue *head = NULL, *tail = NULL;

    while(1)
    {
        switch (menu())
        {
            case 0:
                return 0;

            case 1:
            {
                addElement(&head, &tail);
                break;
            }

            case 2:
            {
                savingFile(head);
                break;
            }

            case 3:
            {
                inputFromFile(&head, &tail);
                break;
            }

            case 4:
            {
                output(head);
                system("pause>0");
                system("cls");
                break;
            }

            case 5:
            {
                search(head);
                break;
            }

            case 6:
            {
                delete(&head, &tail);
                break;
            }
        }
        system("cls");
    }
}
