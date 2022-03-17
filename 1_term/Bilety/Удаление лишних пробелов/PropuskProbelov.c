void fun(char* str)
{
    static int i = 0, i1 = 0, j1 = 0, flag;
    if (str[i]) {
        if (j1- i1 > 1 && flag)
        {
            if (str[j1])
            {
                str[i1 + 1] = str[j1];
                i1++;
                j1++;
            }
            else
            {
                str[i1 + 1] = '\0';
                flag = 0;
            }
            fun(str);
        }
        if (str[i] && str[i] != ' ')
        {
            i1 = i;
            i++;
            flag = 0;
            fun(str);
        }
        if (str[i] == ' ')
        {
            j1 = i;
            i++;
            flag = 1;
            fun(str);
        }
    }
}
