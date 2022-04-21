#include <stdio.h>
#include <stdlib.h>
#include "functionshead.h"
#include "functionsRealisations.c"

int main()
{

	struct base journal;
	journal.pupils = NULL;
	journal.amount = 0;

	while(1)
    {
        switch(menu())
        {
            // Enter pupil
            case 1:{
                journal = enter(journal);
                break;}
            // Output pupil
            case 2:{
                output(journal);
                break;}
            // Change pupil
            case 3:{
                change(journal);
                break;}
            // Search pupil
            case 4:{
                find(journal);
                break;}
            // Sort pupil
            case 5:{
                sort(journal);
                break;}
            // Delete pupil
            case 6:{
                deletion(&journal);
                break;}
            // Partial search
            case 7:{
                partialSearch(journal);
                break;}
            case 0: return 0;
        }
    }
    return 0;
    free(journal.pupils);
}
