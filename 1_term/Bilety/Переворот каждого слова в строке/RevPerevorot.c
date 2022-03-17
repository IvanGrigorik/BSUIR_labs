//Created by SiFi
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *str;
    int size, ns, ks;
    scanf("%d", &size);
    str = (char *)calloc(size + 1, sizeof(char));
    rewind(stdin);
    fgets(str, size, stdin);

    for (int i = 0; i < size; i++)
    {
        while(str[i] == ' ')
            i++;
        ns = i;

        while(str[i] != ' ' && str[i] != '\0')
            i++;
        ks = i - 1;
        revers(str, ns, ks);
    }
    puts(str);

    return 0;
}

void revers(char *str, int ns, int ks)
{
    for( ; ns < ks; ns++, ks--)
    {
        char tmp = str[ns];
        str[ns] = str[ks];
        str[ks] = tmp;
    }
}
