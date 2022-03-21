#include <stdio.h>
#include <stdbool.h>

bool checking (char*, int);
int main (int argc, char *argv[]) { //C:\Users\ivan\Desktop\comstr\cmds "apple not apple apple"
    bool repetion = false;
    printf("your string\n");
    printf("%s \n", argv[1]);

    int firstSimbol, secondSimbol;
    int i = 0;
    firstSimbol = 0;

    while (argv[1][i] != ' ' && argv[1][0] != '\0')
        i++;

    secondSimbol = i+1;

    int firstDeletedSimbol = 0;
    int secondDeletedSimbol = 0;

    while (argv[1][i]) {
        i++;
        firstDeletedSimbol = i;
        repetion = checking(argv[1], firstDeletedSimbol);
        while (argv[1][i] != ' ' && argv[1][i] != '\0') {
            i++;
        }
        if (argv[1][i] == '\0') {
            secondDeletedSimbol = i;
        }
        else {
            secondDeletedSimbol = i + 1;
        }
        if (repetion == true) {
            while ((argv[1][firstDeletedSimbol] = argv[1][secondDeletedSimbol]) != 0){
                firstDeletedSimbol++;
                secondDeletedSimbol++;
            }
        }
    }
    while ((argv[1][firstSimbol] = argv[1][secondSimbol]) != 0) {
        firstSimbol++;
        secondSimbol++;
    }
    printf("your second string\n");
    printf("%s \n", argv[1]);

    return 0;
}

bool checking (char* string, int simbol) {
    int i = 0;
    while (string[i] != ' ') {
        if (string[i] != string[simbol]) {
            return false;
        }
        i++;
        simbol++;
    }
    return true;
}
