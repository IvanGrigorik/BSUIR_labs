//Created by SiFi
#include <stdio.h>

int main(int argc, char **argv)
{ // % - это остаток от деления
  // C:\Users\ivan\Desktop\comstr\cmds
    int sum = 0;
    for (int i = 1; i < argc; i++)
    {
        if (chartoint(argv[i])%4 == 0)
        {
            sum += chartoint(argv[i]);
        }
    }
    printf("Sum is: %d\n", sum);
    return 0;
}

int chartoint(char *str)
{
    int i = 0, razr, znak;
    znak = (str[i] == '-')? -1 : 1;

    if (str[i] == '+' || str[i] == '-')
        i++;

    for(razr = 0; str[i] >= '0' && str[i] <= '9'; i++)
        razr = razr * 10 + (str[i] - '0');

    return znak * razr;

}
