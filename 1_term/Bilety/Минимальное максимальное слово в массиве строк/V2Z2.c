//Created by SiFi
#include <stdio.h>
#include <stdlib.h>


void minslovo(char **str, int nstr, int sstr)
{
    int i, j, k, mindl = 0, dl, nsl, l, imin;

    for (i = 0; i < nstr; i++)
    {
        while (str[i][j] != '\0')
        {
            while (str[i][j] == ' ')
                j++;

            k = j;
            l = i;// Присваиваем для того, чтобы в случае минимального слова оно перенеслость как mindl, только для строки

            while (str[i][j] != ' ' && str[i][j] !='\0')
            {
                dl++;
                j++;
            }

            if (mindl > dl)
            {
                mdl = dl;
                imin = l;
                nsl = k;
            }
            dl = 0;
        }
        i = 0;
    }

    while(str[imin][nsl] != ' ' && str[imin][nsl] != '\0')
    {
        printf("%c", str[imin][nsl]);
        nsl++;
    }
}

void maxslovo(char **str, int nstr, int sstr)
{
    int i, j, k, dl, maxdl = 0, nsl, l, imax;

    for(i = 0; i < nstr; i++)
    {
        while(str[i][j] != '\0')
        {
            while(str[i][j] == ' ')
                j++;

            l = i;
            k = j;

            while (str[i][j] != ' ' & str[i][j] != '\0')
            {
                j++;
                dl++;
            }

            if (maxdl < dl)
            {
                maxdl = dl;
                imax = l;
                nsl = k;
            }
            dl = 0;
        }
        i = 0;
    }

    while (str[imax][nsl] != ' ' && str[imax][nsl] != '\0')
    {
        printf("%c", str[imax][nsl]);
        nsl++;
    }
}
