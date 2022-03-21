int main()
{
    int** a;
    int i, j, k,n = 0;scanf_s("%d", &n);
    a = (int**)malloc(n * sizeof(int*));
    for (i = 0; i < n; i++)
        a[i] =(int*) malloc(n * sizeof(int));
    //Ввод матрицы
    int str,max=0;
    scanf_s("%d",&str);
    for (i = n - 1; i > n - str; i--)
    { max = a[str][i]; k = i;
        for (j = i; j >= n - str; j--)
        {if (a[str][j] > max)
            {max = a[str][j]; k = j;}}
        a[str][k] = a[str][i];
        a[str][i] = max;}}
