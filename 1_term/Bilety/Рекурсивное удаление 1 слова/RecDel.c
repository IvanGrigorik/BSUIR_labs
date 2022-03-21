//Created by SiFi
#include <stdio.h>
#include <malloc.h>

int main ()
{
    char *str;
    int size, i = 0, ns, ks;

    scanf("%d", &size);
    str = (char*)malloc((size+1)*sizeof(char));
    rewind(stdin);

    printf("Enter word for del: ");
    fgets(str, size, stdin);


    while (str[i] == ' ')
        i++;
    ns = i;

    while (str[i] != ' ' && str[i] != '\0')
        i++;

    while (str[i] == ' ')
        i++;
    ks = i;

    sldel(str, ns, ks);
    printf("Str after 1 word del: ");
    puts(str);

    return 0;
}

void sldel(char *str, int ns, int ks)
{
    if((str[ns] = str[ks]) != 0)
    {
        ns++;
        ks++;
        puts(str);
        return sldel(str, ns, ks);
    }
}
