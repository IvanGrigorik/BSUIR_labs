#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Ввод количества строк матрицы
    int size;
    printf_s("Enter square matrix size\n>>> ");
    while(!scanf("%d", &size) || size <= 1)
    {
        printf_s("Please, enter correct size \n>>> ");
        fflush(stdin);
    }

    // Выделение памяти под матрицу
    int **matrix;
    printf_s("Enter matrix with size %d\n>>> ", size);
    matrix = (int **)malloc(sizeof(int *) * size);
    for(int i = 0; i < size; i++)
        matrix[i] = (int *)calloc(size, sizeof(int));

    // Ввод матрицы
    for(int i = 0; i < size; i++)
    {

        for(int j = 0; j < size; j++)
        {
            while(!scanf_s("%d", &matrix[i][j]))
            {
                printf_s("Enter numbers\n Enter [%d] line\n>>> ", j + 1);
                fflush(stdin);
            }
        }
        printf_s(">>> ");
    }

    printf("Sum is: %d", fun(matrix, size));

}




int fun(int** mt, int s)
{
    static int i = 1, j, count = 5, sum;
    if (i < s) {
        if (j < i)
        {
            if (mt[i][j] % 2 != 0 && count)
            {
                sum += mt[i][j];
                count--;
            }
            j++;
            fun(mt, s);
        }
        else
        {
            i++;
            j = 0;
            fun(mt, s);
        }
    }
    return sum;
}

