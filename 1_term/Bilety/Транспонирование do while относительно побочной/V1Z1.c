//Created by SiFi
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int **a;
    int i, j, n;
    scanf_s("%d", &n);
    a = (int**)malloc(n * (sizeof(int*)));
    for (i = 0; i < n; i++)
        a[i] = (int*)malloc(n * (sizeof(int)));

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            a[i][j] = rand() % 20 + 10;
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    printf("\n");

    trans(a, n);

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

int trans(int **matrix, int size)
{
    int i = 0, j = 0;
    do
    {
        do
        {
            int c;
            c = matrix[i][j];
            matrix[i][j] = matrix[size - j - 1][size - i - 1];
            matrix[size - j - 1][size - i - j] = c;
            j++;
        }while (j < size-i-1);
        i++;
        j = 0;
    }while (i < size);
}

/* Через for
int trans(int **matrix, int size)
{
    int i = 0, j = 0;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size - i - 1; j++)
        {
            int tmp;
            tmp = matrix[i][j];
            matrix[i][j] = matrix[size - j - 1][size - i - 1];
            matrix[size - j - 1][size - i - 1] = tmp;
        }
    }
}
*/

/* Через while
int trans(int **matrix; int size)
{
    int i = 0, j = 0;

    while (i < size)
    {
        for (j < size - i - 1;)
        {
            int tmp;
            tmp = matrix[i][j];
            matrix[i][j] = matrix[size - j - 1][size - i - 1];
            matrix[size - j - 1][size - i - 1] = tmp;
            j++
        }
        i++;
    }
}
*/
