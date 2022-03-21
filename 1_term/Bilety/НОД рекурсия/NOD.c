//Created by SiFi

int main(void)
{
    int i, a, b;
    scanf("%d", &a);
    scanf("%d", &b);

    printf("NOD is: %d", nod(a, b));
    return 0;
}


int nod(int a, int b)
{
    int c;
    if (b > a)
        c = nod (b, a);
    else if (b<=0)
        c = a;
    else
    {
        c = nod (b, a%b);
        printf("%d", nod(b, a%b));
    }
    return c;
}
