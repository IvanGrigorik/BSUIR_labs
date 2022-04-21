#include <stdio.h>
#include <stdlib.h>
#include "head.h"

int main()
{
    struct stack *database = NULL;
    FILE *binaryFile = NULL;
    FILE *textFile = NULL;

    int choice;

    do
    {
        puts("Enter 1 to input from file");
        printf("Enter 2 to continue without file\n>>> ");
        choice = check();
        system("cls");
    }while(choice < 0 || choice > 2);

    if(choice == 1)
        inputFromFile(&database, binaryFile, textFile);

    system("cls");

    while(1)
    {
        switch(menu())
        {
            // Add tour's
            case 1:{
                addElement(&database);
                break;}

            case 2:{
                saveFileElement(&database, binaryFile, textFile);
                break;}

            // Output tour's
            case 3:{
                output(database);
                system("pause>0");
                break;}

            // Search tour's
            case 4:{
                search(database);
                break;}

            // Delete tour's
            case 5:{
                delete(&database);
                break;}

            // End process
            case 0:
                return 0;
        }
        system("cls");
    }

    return 0;
}
