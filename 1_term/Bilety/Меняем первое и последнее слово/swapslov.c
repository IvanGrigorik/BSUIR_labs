//Created by SiFi
#include <stdio.h>
#include <stdlib.h>

int main ()
{
    char *str;
    int size, FirstWordN, FirstWordK, LastWordN, LastWordK, i = 0;

    scanf("%d", &size);

    str = (char *)calloc(size + 1, sizeof(char));
    rewind(stdin);
    fgets(str, size , stdin);

    while (str[i] == ' ')
        i++;
    FirstWordN = i;

    while(str[i] != ' ')
        i++;
    FirstWordK = i - 1;

    while(str[i] != '\0')
        i++;
    LastWordK = i - 1;

    while (str[i] != ' ')
        i--;
    LastWordN = i + 1;

    revers(str, FirstWordN, FirstWordK);
    puts(str);
    revers(str, LastWordN, LastWordK);
    puts(str);
    revers(str, FirstWordK + 1, LastWordN - 1);
    puts(str);
    revers(str, FirstWordN, LastWordK);
    puts(str);

    return 0;
}
void revers(char *str, int ns, int ks)
{
    if(ns < ks)
    {
        char tmp = str[ns];
        str[ns] = str[ks];
        str[ks] = tmp;
        ns++;
        ks--;
        return revers(str, ns, ks);
    }
}
