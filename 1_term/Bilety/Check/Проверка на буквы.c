#include <stdio.h>

int check(int x)
{
    char y;
    while ( !(scanf_s("%d%c", &x, &y)) || y != '\n' || x <= 1)
    {
        rewind(stdin);
        puts("Please, enter correct size: ");
    }
    return x;
}
