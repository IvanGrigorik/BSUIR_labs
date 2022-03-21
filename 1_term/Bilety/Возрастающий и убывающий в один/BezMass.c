//Created by SiFi
#include <stdio.h>
#include <locale.h>
#define n 3
#define m 5

int main()
{
    int mas1[m], mas2[n], mas3[m+n], i1, i2, i3;
    printf("Vozr");
    for(i1=0;i1<n;i1++)// ввод первого массива
        scanf("%d",&mas1[i1]);
    printf("Ub");
    for(i2=0;i2<m;i2++) // ввод второго массива
        scanf("%d",&mas2[i2]);

    i1 = 0;
    i2 = m-1;
    i3 = 0;

    while(i1<n && i2>=0) // пока в двух массивах есть элементы
    {
        while(mas1[i1]<=mas2[i2] && i1<n) // запись первого массива пока его элемент наименьший
            mas3[i3++]=mas1[i1++];

        while(mas2[i2]<mas1[i1] && i2>=0) // запись второго массива пока его элемент наименьший
            mas3[i3++]=mas2[i2--];
    }

    while(i1<n)
        mas3[i3++]=mas1[i1++];
    while(i2>=0)
        mas3[i3++]=mas2[i2--];

    for(i3=0;i3<(n+m);i3++)
        printf("%3d",mas3[i3]);


    return 0;
}
