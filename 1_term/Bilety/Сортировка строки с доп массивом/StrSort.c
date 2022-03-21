void sort(char *in, char *out)
{char *max_word;
    while((max_word=find(in)))
    {
        for (; *max_word!=' ' && *max_word!='\0'; )
        {
            *(out++) = *max_word;
            *(max_word++) =' ';
        }
        *(out++) =' ';
    }
    *(out--)='\0';
}
