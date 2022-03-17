//Created by SiFi
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int a[3][4], a1[4][2], a2[3][2], i = 0, j = 0, k = 0;

    /*"функция сканирования для a, a1"*/

    do
    {
        j = 0;
        do
        {
            a2[i][j] = 0;
            k = 0;
            do
            {
                a2[i][j] += a[i][k] * a1[k][j];
                k++;
            }while (k<4);
            j++;
        }while(j<2);
        i++
    }while(i<3);

    for (i = 0; i < n2; i++)
    {
        for (j = 0; j < m1; j++)
            printf("%d ", a2[i][j]);
        printf("\n");
    }

    return 0;
}
do
{
    j = 0;
    do
    {
        a2[i][j] = 0;
        k = 0;
        do
        {
            a2[i][j] += a[i][k] * a[k][j];
            k++;
        }while(k < 4);
        j++;
    }while(j < 2);
    i++;
}while(i < 3)
