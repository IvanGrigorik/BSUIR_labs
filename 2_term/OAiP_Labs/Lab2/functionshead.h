#ifndef FUNCTIONSHEAD_H_INCLUDED
#define FUNCTIONSHEAD_H_INCLUDED

union information
{
    char date[9];
    int duration;
};

struct tour
{
    union information info;
    int cost;
    char *name;
    int indicator;
};

struct base
{
    int amount;
    struct tour *tours;
};

//################################################
int menu();
int check();
int findmax (struct base toursList, int code);
char *MyItoA(int num);
//################################################
struct base enter(struct base toursList);
char *getString(void);
int getDigits(int i, struct base toursList);
struct base enterNameCost(int i, struct base toursList);
//################################################
void spacePrint(int i);
void output(struct base toursList);
void outputAll(struct base toursList, int choise);
void outputHead(struct base toursList, int indicator);
void outputOne(int i, struct base toursList, int choise);
void printfLongest(struct base toursList);
//################################################
void find(struct base toursList);
void uppercase(char find[20]);
//################################################
struct base deletion(struct base *toursList);
void deleteOne(struct base *tourList, int *amount ,int i);

#endif // FUNCTIONSHEAD_H_INCLUDED
