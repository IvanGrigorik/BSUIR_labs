#include<stdio.h>
#include<malloc.h>
#include<stdarg.h>

char* fun(int k, ...)
{
	int i = 0,begin=0,end=0, min_begin = 0,min_end =0,min=0 ;
	char *word,*str;
	va_list p;
	va_start(p, k);
	word = (char*)malloc(1 * sizeof(char));
	str = va_arg(p, char*);

	int m = 0;

	while (str[m] == ' ')
	{
		m++;
		min_begin = m;
	}
	while (str[m] != ' ' && str[m] != '\0')
	{
		min_end = m;
		m++;
	}
	min = min_end - min_begin;

	for (int j = 0; j < k; j++)
	{
		m = 0;
			while (str[m])
			{
				while (str[m] == ' ')
				{
					m++;
					begin = m;
				}
				while (str[m] != ' ' && str[m] != '\0')
				{
					end = m;
					m++;
				}

				if ((end - begin) < min)
				{
					min = end - begin;
					min_end = end;
					min_begin = begin;

					word = (char*)realloc(word,(min_end - min_begin) * sizeof(char));
					int n,i1;
					for (i1=0, n = min_begin; n <= min_end;i1++, n++)
					{
						word[i1] = str[n];
					}
					word[n] = '\0';
				}
			}
			str = va_arg(p, char*);
	}
	va_end(p);
	return word;


}
int main()
{
	int j,i,k = 3;
	char** text;
	rewind(stdin);
	text = (char**)malloc(k * sizeof(char*));
	for (i = 0; i < k; i++)
		*(text + i) = (char*)malloc(1 * sizeof(char));
	rewind(stdin);
	j = 0;
	for (i = 0; i < k; i++)
	{

		while ((text[i][j++] = getchar()) != '\n')
		{
			text[i] = (char*)realloc(text[i], (j + 1) * sizeof(char));

		}
		text[i][j - 1] = '\0';
		j = 0;

	}
	printf("%s", fun(3, text[0], text[1], text[2]));


	return 0;

}
