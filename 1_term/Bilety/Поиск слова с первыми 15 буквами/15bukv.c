//Created by SiFi
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int size, i = 0, s = 0, ns;
    scanf("%d", &size);
    char *str;
    str = (char*)calloc(size + 1, sizeof(char));
    rewind(stdin);
    fgets(str, size, stdin);

    while(str[i] != '\0')
    {
        while(str[i] == ' ')
            i++;
        if(str[i] >= 'a' && str[i] <= 'o')
        {
            ns = i;
            while(str[i] >= 'a' && str[i] <= 'o')
            {
                i++;
                s++;
            }
        }
            i++;
    }


    while(ns<s)
    {
        printf("%c", str[ns]);
        ns++;
    }

    return 0;
}
