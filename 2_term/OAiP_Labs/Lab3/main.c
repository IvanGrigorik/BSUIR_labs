#include <stdio.h>
#include <stdlib.h>
#include "head.h"

int main()
{
    int choiseFile;
    do
    {
        puts("What file you want to open?");
        puts("Enter:");
        puts("1 - to open text file");
        printf("2 - to open binary file\n>>> ");
        choiseFile = check();
        system("cls");
    }while(choiseFile < 1 || choiseFile > 2);

    if(choiseFile == 1)
    {
        char *fileName;
        do
        {
            system("cls");
            printf("Enter file name: ");
            rewind(stdin);
        }while(!(fileName = getFileName(1)));

        FILE *textFile = NULL;
        system("cls");

        while(1)
        {
            switch(menuText())
            {
                case 1:{
                    enterTextFile(textFile, fileName);
                    break;}
                case 2:{
                    outputText(textFile, fileName);
                    break;}
                case 3:{
                    occurText(textFile, fileName);
                    break;}
                case 4:{
                    move(textFile, fileName);
                    break;}
                case 0:{return 0;}
                default:{
                    system("cls");
                    break;}

            }
        }
    }

    if (choiseFile == 2)
    {
        char *fileName;
        do
        {
            system("cls");
            printf("Enter file name: ");
            rewind(stdin);
        }while(!(fileName = getFileName(2)));

        FILE *binaryFile = NULL;
        system("cls");

        while(1)
        {
            switch(menuBin())
            {
                case 1:{
                    enterBinaryFile(binaryFile, fileName);
                    break;}
                case 2:{
                    outputBinary(binaryFile, fileName);
                    break;}
                case 3:{
                    oneElement(binaryFile, fileName);
                    break;}
                case 4:{
                    swapElements(binaryFile, fileName);
                    break;}
                case 0:{
                    return 0;}
                default:{
                    system("cls");
                    break;}
            }
        }
    }
}

