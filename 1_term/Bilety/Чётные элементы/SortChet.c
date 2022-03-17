void func(int** a,int n)
{
    int i=0, j, k, left=0, right=n-1, flag=1;
    while (i < n)
    {
        if (a[i][0] % 2==0)
        {
            while (left < right && flag)
            {
                flag = 0;
                for (j = left; j < right; j++)
                {
                    if (a[i][j] > a[i][j + 1])
                    {
                        int c;
                        c = a[i][j];
                        a[i][j] = a[i][j + 1];
                        a[i][j + 1] = c;
                        flag = 1;
                    }
                }
                right--;
                for (j = right; j > left; j--)
                {
                    if (a[i][j] < a[i][j - 1])
                    {
                        int c;
                        c = a[i][j];
                        a[i][j] = a[i][j - 1];
                        a[i][j - 1] = c;
                        flag = 1;
                    }
                }
                left++;
            }
            i++;
            left = 0;
            right = n - 1;
            flag = 1;
        }
        else
        i++;
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}
