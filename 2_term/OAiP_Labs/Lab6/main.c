#include "fun.h"

int main(void)
{
    setbuf(stdout, NULL);

    struct tree *root = NULL;

    while(1)
    {
        switch(menu())
        {
            // Ввод дерева
            case 1:
                input(&root);
                root = balance(root);
                break;

            case 2:
                puts("Vocabulary:");
                system("cls");
                show(root);
                system("pause>0");
                break;

            case 3:
                puts("Vocabulary:\n");
                showTreeByStack(root);
                break;

            case 4:
                print(root, 0);
                system("pause>0");
                break;

            case 5:
                delete(&root);
                break;

            case 6:
                deleteAll(&root);
                break;

                // Test
            case 7:

                break;


            case 0:
                deleteAll(&root);
                puts("tree now is free");
                system("pause>0");
                return 0;
        }

    }
}
