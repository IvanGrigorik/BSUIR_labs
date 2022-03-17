//Created by SiFi
#include <stdio.h>
#include <math.h>
static int factorial (int n);
float power(float x, int y);
int main()
{
    float e, x, n = 1;
    int k;
    scanf("%f", &e);
    scanf("%f", &x);
    scanf("%d", &k);
    float res = x, lastRes;
    do
    {
        lastRes = res;
        res = lastRes + (power(-1, n) * factorial(2 * n + 1) / power(x - 2 * n,2 * n));
        printf("%.0f\t%f\n", n, res);
        n++;
    } while (abs(res - lastRes) > k && res != e);
    printf("%lf", res);
    return 0;
}
static int factorial (int n)
{return (n < 2) ? 1 : n * factorial (n - 1);}
float power(float x, int y) {
    int i;
    float rez = 1;

    for(i = 1; i <= y; ++i) {
        rez *= x;
    }
    return rez;
}

