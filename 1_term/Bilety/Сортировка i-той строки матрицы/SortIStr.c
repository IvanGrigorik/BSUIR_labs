#include <stdio.h>
#include <stdlib.h>



int main()
{
    int** a, n, i, j, m,k;
    scanf_s("%d", &n);
    scanf_s("%d", &m);
    scanf_s("%d", &k);
    a = (int**)malloc(n * sizeof(int**));
    for (i = 0; i < n; i++)
    a[i] = (int*)malloc(m * sizeof(int*));
    for (i = 0; i < n; i++)
    {
    for (j = 0; j < m; j++)
    {
    a[i][j] = rand() % 20 + 10;
    printf("%d ", a[i][j]);
    }
    printf("\n");
    }
    printf("\n");
    for (i = 1; i < m; i++)
    {
    j = i;
    while (a[k][i]< a[k][j - 1] && j-1>=0)
    {
    a[k][j] = a[k][j - 1];
    j--;
    }
    a[k][j] = a[k][i];
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}
