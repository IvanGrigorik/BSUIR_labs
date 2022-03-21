//Created by SiFi
#include <stdio.h>
#include <stdlib.h>
void perevod(double num, int ss, int n);
int main()
{
    double n;
    scanf("%lf", &n);
    int sys;
    scanf("%d", &sys);
    int toch;
    scanf("%d", &toch);
    perevod(n, sys, toch);
    return 0;
}

void perevod(double num, int ss, int n)
{
    static int i = 0, j;
    int znak;
    static char str[286];
    if (num < 0)
    {
        znak = -1;
        num *= -1;
    }
    if (num != 0 && n)
    {
        num *= ss;
        j = (int)num;
        num -= j;
        str[i] = j < 10 ? j + '0' : j - 10 + 'a';
        i++;
        return perevod(num, ss, n - 1);
    }
    str[i] = '\0';
    printf("0.");
    puts(str);
}
