int** func(int** a, int n)
{
    static int i;
    if (i<n/2)
    {
        int c;
        c = a[i][n-1-i];
        a[i][n-1-i] = a[n-1-i][i];
        a[n-1-i][i] = c;i++;
        return func(a, n);
    }
    return a;
}
