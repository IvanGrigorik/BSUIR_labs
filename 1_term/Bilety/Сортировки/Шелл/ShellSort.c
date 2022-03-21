//Created by SiFi
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *mass;
    int size;
    scanf("%d", &size);
    mass = (int*)calloc(size, sizeof(int));
    for(int i = 0; i < size; i++)
        scanf("%d", &mass[i]);

    mass = ShellSort(mass, size);

    for(int i = 0; i < size; i++)
        printf("%d ", mass[i]);

    return 0;
}
    mass = ShellSort(mass, size);
int ShellSort(int *mass, int N)
{
    int step, i, j, tmp;
	for (step = N / 2; step > 0; step = step/2)
    {for (i = step; i < N; i++)
		{for (j = i - step; j >= 0 && mass[j] > mass[j + step]; j -= step)
			{tmp = mass[j];
             mass[j] = mass[j + step];
             mass[j + step] = tmp;}}}
    return mass;
}
