//Created by SiFi

void func(int** a, int** b, int n, int n1, int m, int m1, int** c)
{
    int i = 0, j = 0, k, s, i1 = 0, j1 = 0, i2 = 0, j2 = 0;
    do{
        do{
            do{
                c[i][j] += a[i1][j1] * b[i2][j2];
                j1++;
                i2++;
                }while (j1 < m);
            i2 = 0;j1 = 0;j2++;j++;
            }while (j < m1);
        i2 = j2 = j1 = 0;i1++;i++;j = 0;
        }while (i < n);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m1; j++)
            printf("%d ", c[i][j]);
        printf("\n");
    }
}
