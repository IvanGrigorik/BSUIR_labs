//Created by SiFi
#include <stdio.h>

void f(){static short int pos = 0;
    long int num;
    if (pos != 0 && getchar() == '\n')
    {
        pos--;
        return;
    }
    scanf("%ld", &num);
    pos++;
    f();
    printf("%hi) %li\n", pos+1, num);
    pos--;}

int main()
{
    f();
    return 0;
}

