//Created by SiFi
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int m, n, i, j;
  scanf("%d", &n);
  scanf("%d", &m);

  int **mx = (int **)malloc(m * sizeof(int *));
  for (i = 0; i < m; ++i)
    mx[i] = (int *)malloc(n * sizeof(int));

  for (i = 0; i < m; ++i)
  {
    for (j = 0; j < n; ++j)
    {
        printf("[%d][%d]", i, j);
      mx[i][j] = check(mx[i][j]);
    }
  }

  sedlo(mx, m, n);

  for (i = 0; i < m; ++i)
    free(mx[i]);

  free(mx);

  return 0;
}
/*
void sedlo(int **mx, int n, int m)
{
    int i, j, k, is_sedlo;
    for (i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            is_sedlo = 1;

            for(k = 0; k < n; k++)
            {
                if (mx[i][j] < mx[k][j] && k!=i)
                    is_sedlo = 0;
            }

            for (k = 0; k < m; k++)
            {
                if(mx[i][j] > mx[i][k] && k != j)
                    is_sedlo = 0;
            }
        if(is_sedlo)
            printf("%d ", mx[i][j]);
        }
    }
    return;
}*/

void sedlo(int **a, int m, int n)
{
    int i, j, k, is_sedlo;
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            is_sedlo = 1;
            for(k = 0; k < m; k++)
            {
                if(a[i][j] < a[k][j] && k!=i)
                    is_sedlo = 0;
            }
            for(k = 0; k < n; k++)
            {
                if(a[i][j] > a[i][k] && k!=j)
                    is_sedlo = 0;
            }
            if(is_sedlo)
            printf("%d ", a[i][j]);
        }

    }
    return;
}

int check(int x)
{
    char y;
    while (!(scanf_s("%d%c", &x, &y)) || y != '\n')
    {
        rewind(stdin);
        puts("Please, enter correct n: ");
    }
    return x;
}
