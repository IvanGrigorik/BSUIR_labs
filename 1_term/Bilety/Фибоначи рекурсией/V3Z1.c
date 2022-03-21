//Created by SiFi

int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        printf("%d, ", fibon(i));
}

int fibon(int n)
{
    return (n == 0 || n == 1)? 1:fibon(n-1)+fibon(n-2);
}
