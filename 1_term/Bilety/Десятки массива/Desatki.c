#include <stdio.h>
#include <stdlib.h>

int main()
{
    int size, d = 0;
    int* ms, *ms_d;
    scanf("%d", &size);
    ms = (int*)calloc(size, sizeof(int));
    ms_d = (int*)calloc(1, sizeof(int));
    for(int i = 0; i < size; i++)
            scanf("%d", &ms[i]);

    for(int i = 0; i < size; i++)
    {
        int tmp;
        tmp = ms[i]/10;
        printf("chislo %d, des %d\n", ms[i], tmp);
    }

}
