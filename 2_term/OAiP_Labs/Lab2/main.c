#include <stdio.h>
#include <stdlib.h>
#include "functionshead.h"
#include "functionsRealisations.c"

int main()
{
    struct base toursList;
    toursList.amount = 0;
    toursList.tours = NULL;

    while(1)
    {
        switch(menu())
        {
            // Enter tour's
            case 1:{
                toursList = enter(toursList); break;}
            // Output tour's
            case 2:{
                output(toursList); break;}
            // Search tour's
            case 3:{
                find(toursList); break;}
            case 4:{
                deletion(&toursList); break;}
            case 5:{
                printfLongest(toursList); break;}
            case 0:
                return 0;
        }
        system("cls");
    }
    free(toursList.tours);
}
