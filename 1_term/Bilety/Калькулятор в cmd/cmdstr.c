int main(int argc, char **argv)
{
    for (i = 1; i < argc; i++) // 1 - потому что 0 - это путь к файлу
    {
        if(*argv[i] == '+') int sum = chartoint(argv[i-1]) + chartoint(argv[i+1]);
        if(*argv[i] == '-') int sum = chartoint(argv[i-1]) - chartoint(argv[i+1]);
        if(*argv[i] == '/') int sum = chartoint(argv[i-1]) / chartoint(argv[i+1]);
        if(*argv[i] == '#') int sum = chartoint(argv[i-1]) * chartoint(argv[i+1]);
    }
    return 0;
}

int chartoint(char *str)
{
    int i = 0, znak, razr = 0;
    znak = (str[i] == '-')? -1 : 1;
    if (str[i]=='-' || str[i]=='+')
        i++;

    for(razr = 0; str[i]>= '0' && str[i]<= '9'; i++)
        razr = razr * 10 + (str[i] - '0');

    return znak*razr;
}
