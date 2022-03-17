//Created by SiFi

int main()
{
    int** a,i,j,k,n=7;
    a = (int**)malloc(n * sizeof(int**));
    for (i = 0; i < n; i++)
    a[i] = (int*)malloc(n * sizeof(int*));
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            a[i][j] = rand() % 40 + 10;
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    for (i = 1; i < n; i++)
    {
        k = a[i][i];
        j = i;
        while (j && k > a[j - 1][j - 1])
        {
        a[j][j] = a[j - 1][j - 1];
        j--;
        }
        a[j][j] = k;
    }
    printf("\n");
    printf("\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d ", a[i][j]);
        }
    printf("\n");
    }
}
