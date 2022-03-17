// В мэйн fun(argv, argc)
int fun(char** s, int n)
{
    static char** p;
    static int max, med, flag, num, maxnum, word;
    if (n)
    {
        if (!word)
        {
            flag = 1;
            p = s;
        }
        if (**p)
        {
            if (**p == ' ')
            {
                (*p)++;
                flag = 1;
                word = 0;
                fun(s, n);
            }
            if (**p && **p != ' ')
            {
                if(**p >= 'A' && **p <= 'Z' && flag == 1)
                {
                    med++;
                    (*p)++;
                    flag = 0;
                    word = 1;
                    fun(s, n);
                }
                else
                {
                    (*p)++;
                    flag = 0;
                    word = 1;
                    fun(s, n);
                }
            }
        }
        if (med >= max)
        {
            max = med;
            maxnum = num;
        }
        num++;
        fun(++s, --n);
    }
    return maxnum;
}
