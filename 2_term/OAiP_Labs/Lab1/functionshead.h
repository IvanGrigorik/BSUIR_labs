#ifndef FUNCTIONSHEAD_H_INCLUDED
#define FUNCTIONSHEAD_H_INCLUDED
struct pupil
{
	char name[20];
	char lastName[20];
	char patronymic[20];
	char number[10];
	int clas;
	int marks[4];
};

struct base
{
    struct pupil *pupils;
    int amount;
};

int menu();
int check(int x);
int digitsGet(int i, struct base journal);
int strGet(int i, struct base journal, char *code);
void showExam();
void showMenu(char *s);
void uppercase(char find[20]);
void sort(struct base journal);
void find(struct base journal);
void output(struct base journal);
void change(struct base journal);
void partialSearch(struct base journal);
void outputOne(int i, struct base journal);
struct base enter(struct base journal);
struct base deletion(struct base *journal);

#endif // FUNCTIONSHEAD_H_INCLUDED
