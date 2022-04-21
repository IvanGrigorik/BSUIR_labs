#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

char *MyItoA(int num);
int numberLength(int number);
void printNull(FILE* textFile, int number);
int check(void);
int menuText();
int menuBin();
char *getFileName(int code);
void enterTextFile(FILE *textFile, char *fileName);
void enterBinaryFile(FILE *binaryFile, char *fileName);
void outputText(FILE *textFile, char *fileName);
void outputBinary(FILE *binaryFile, char *fileName);
void occurText(FILE *textFile, char *fileName);
void move(FILE *textFile, char *fileName);
void oneElement(FILE *binaryFile, char *fileName);
void swapElements(FILE *binaryFile, char *fileName);


#endif // HEAD_H_INCLUDED
