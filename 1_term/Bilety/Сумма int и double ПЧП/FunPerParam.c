//Created by SiFi
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
void ** var_fun(int, ...);
int main()
{
	float d1 = 1.1, d2 = 2.2, d3 = 3.3, d4 = 4.4;
	int i1 = 5, i2 = 6, i3 = 7, i4 = 8;
	void **ms;              // для возврата из var_fun адресов (двух) полученных сумм
	puts("int\n");
	scanf("%d%d%d%d",&i1,&i2,&i3,&i4);
	puts("double\n");
	scanf("%f%f%f%f",&d1,&d2,&d3,&d4);
	ms = var_fun(3, 'f', 3, d1, d2, d3, 'i', 4, i1, i2, i3, i4, 'f', 2, d3, d4);
	puts("\n\nresult main :");
	printf("\n  sum int= %d  sum float= %5.2f\n", *((int*)*ms), *((double*)*(ms + 1)));
	free(ms[0]); free(ms[1]); free(ms);
	return 0;
}


void **var_fun(int n, ...)
{
    int i, j;
    void **sum = (void **)calloc(2, sizeof(int*));
    *((int**)sum+0) = (int*)calloc(1, sizeof(int*));
    *((double**)sum+1) = (double*)calloc(1, sizeof(double*));
    char c;
    va_list p;
    va_start(p, n);
    while(n--)
    {
        c = *(char *)p;
        i = *(int *)p;
        switch(c)
        {
            case 'f': for(j = 0; j<i; j++)
            {
                **((double**)sum+1) += va_arg(p, double);
            }
            break;
            case 'i': for(j = 0; j<i; j++)
            {
                **((int**)sum+0) += va_arg(p, int);
            }
            break;
        }
    }
    va_end(p);
    printf("sum int: %d, sum double: %d", **((int**)sum), **((double**)sum + 1));
    return sum;
}
