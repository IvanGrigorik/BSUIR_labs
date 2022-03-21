//Created by SiFi
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int n;

  printf("n: ");
  scanf("%d", &n);

  rewind(stdin);

  putchar('\n');

  int i, j;

  int **mx = (int **)malloc(n * sizeof(int *));

  for (i = 0; i < n; ++i)
    mx[i] = (int *)malloc(n * sizeof(int));

  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {
      printf("[%d][%d]: ", i, j);
      scanf("%d", &mx[i][j]);
      rewind(stdin);
    }

    putchar('\n');
  }

  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j)
      printf("%3d", mx[i][j]);

    putchar('\n');
  }

  putchar('\n');

  /* ВЫБЕРИ ПРАВИЛЬНУЮ ФУКНЦИЮ, ЧТОБЫ ВЫЖИТЬ!11!!1! */
    recur(mx, n);

  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j)
      printf("%3d", mx[i][j]);

    putchar('\n');
  }

  for (i = 0; i < n; ++i)
    free(mx[i]);

  free(mx);

  return 0;
}



void recur(int **matrix, int size)
{
    static int i = 1;
    static int j = 0;

    int tmp = matrix[i][j];
    matrix[i][j] = matrix[j][i];
    matrix[j][i] = tmp;

    if (++j < i)
        return recur(matrix, size);

    if (++i < size)
        return j = 0, recur(matrix, size);
    return;
}

void recour_poboch(int **matrix, int size)
{
    static int i = 0;
    static int j = 0;

    int tmp = matrix[i][j];
    matrix[i][j] = matrix[size - j - 1][size - i - 1];
    matrix[size - j - 1][size - i - 1] = tmp;

    if (size - 1 > i++)
        return j = 0, recour_poboch(matrix, size);
    if (j < size - i - 1)
        return recour_poboch(matrix, size);

    return;
}

void trans_main(int **matrix, int size)
{
    for (int i = 1; i < size; i++)
    {
        for (int j = 0; j < i; j++)
        {
            int tmp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = tmp;
        }
    }
    return;
}

void trans_poboch(int **matrix, int size)
{
    for(int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            int tmp = matrix[i][j];
            matrix[i][j] = matrix[size - j - 1][size - i - 1];
            matrix[size - j - 1][size - i - 1] = tmp;
        }
    }
}
