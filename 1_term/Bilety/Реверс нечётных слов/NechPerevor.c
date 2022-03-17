//Created by SiFi
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Реверс нечётных слов
    char *str;
    int size;
    int i = 0, ns, ks;
    scanf("%d", &size);
    str = (char*)calloc(size + 1, sizeof(char));
    rewind(stdin);
    fgets(str, size, stdin);

    while(str[i] != '\0')
    {
        while(str[i] == ' ')
            i++;
        ns = i;
        while(str[i] != ' ' && str[i] != '\0')
            i++;
        ks = i - 1;
        revers(str, ns, ks);
        while(str[i] == ' ')
            i++;
        while(str[i] != ' ' && str[i] != '\0')
            i++;
    }
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
