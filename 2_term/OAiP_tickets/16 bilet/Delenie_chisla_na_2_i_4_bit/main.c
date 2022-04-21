#include <stdio.h>

// Получить остаток числа от деления на 4 и 2,
// используя поля бит

struct div_2
{
    unsigned int div_2 : 1;
    int : 15;
};

struct div_4
{
    unsigned int div_4 : 2;
    int : 14;
};

union div
{
    unsigned int num;
    struct div_2 d;
    struct div_4 d2;
};

int main()
{
    union div divNum;
    scanf("%u", &divNum.num);
    printf("%u", divNum.d.div_2);
    printf("%u", divNum.d2.div_4);
}

