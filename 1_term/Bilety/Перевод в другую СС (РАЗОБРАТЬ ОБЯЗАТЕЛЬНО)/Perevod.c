#include <stdio.h>
#include <stdlib.h>

void strnrev(char *str, int n)
{
  char *tmp = str + n - 1;

  while (str < tmp) {
    char c = *str;
    *str++ = *tmp;
    *tmp-- = c;
  }
  return;
}

void perevod(double num, int sys, int prec)
{
  int sign = 1;

  if (num < 0)
    sign = -1, num *= -1;

  int i_num = (int)num;
  num -= i_num;

  char str[32];

  int i = 0, j;

  do {
    j = i_num % sys;
    str[i++] = j < 10 ? j + '0' : j - 10 + 'a';
    i_num /= sys;
  } while (i_num > 0);

  if (sign == -1)
    str[i++] = '-';

  strnrev(str, i);

  str[i++] = '.';

  while (num != 0 && prec) {
    num *= sys;
    j = (int)num;
    num -= j;

    str[i++] = j < 10 ? j + '0' : j - 10 + 'a';

    --prec;
  }

  str[i] = '\0';

  printf("\n%s\n", str);

  return;
}

int main(void)
{
  double num;

  printf("num: ");
  scanf("%lf", &num);

  rewind(stdin);

  int sys;

  printf("sys: ");
  scanf("%d", &sys);

  rewind(stdin);

  int prec;

  printf("prec: ");
  scanf("%d", &prec);

  perevod(num, sys, prec);

  return 0;
}
