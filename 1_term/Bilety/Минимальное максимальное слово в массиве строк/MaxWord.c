//Created by SiFi
#include <stdio.h>
#include <stdlib.h>

void maxslovo(char **a,/*S*/ int nstrok, /*n*/int sizestrok)
{
    int maxdl = 0, maxn, dl = 0, i, j = 0, k = 0, imax, l;

    for(i = 0; i < nstrok; i++)
    {
        while (a[i][j] != '\0')
        {
            while (a[i][j] == ' ')
                j++;

            k = j;
            l = i;

            while (a[i][j] != ' ' && a[i][j] != '\0')
            {
                j++;
                dl++;
            }

            if (maxdl < dl)
            {
                maxdl = dl;
                maxn = k;
                imax = l;
            }
            dl = 0;
        }
        i = 0;
    }

    while(a[imax][maxn] != ' ' &&a[imax][maxn] != '\0')
    {
        printf("%c", a[imax][maxn]);
        maxn++;
    }
    printf("\n");
}

void minslovo(char **str, int nstr, int sstr)
{
    int i, j = 0, k = 0, dl = 0, mdl = 0, l, imin, msym; // msym - символ начала минимального слова

    for (i = 0; i < nstr; i++)
    {
        while (str[i] != '\0')
        {
            while(str[i][j] == ' ')
                j++;

            k = j;
            l = imin;

            while (str[i][j] != ' ' && str[i][j] != '\0')
            {
                j++;
                dl++;
            }

            if (mdl > dl)
            {
                mdl = dl;
                msym = k;
                imin = l;
            }

            dl = 0;
        }
        i = 0;
    }

    while (str[imin][msym] != ' ' && str[imin][msym] != '\0')
    {
        printf("%c", str[imin][msym]);
        msym++;
    }

}
