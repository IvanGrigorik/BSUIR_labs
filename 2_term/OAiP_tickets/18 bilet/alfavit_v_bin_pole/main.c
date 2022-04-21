#include <stdio.h>

/*
 * Записать в битовом представлении буквы алфавита
 *
 * И тут есть пару "но":
 * 1) Если имеется в виду, что надо получить номер
 *    каждой буквы согласно алфавиту, то не составит
 *    проблем написать что-то типо этого:

  // 5 букв, потому что этого хватит, чтобы вывести номер любой буквы (2^5 = 32, а в английском алфавите 21/32 буквы)
  struct oneByte
  {
      unsigned int a : 1;
      unsigned int b : 1;
      unsigned int c : 1;
      unsigned int d : 1;
      unsigned int e : 1;
      int : 3;
  };

  union oneSymbol
  {
      char letter;
      struct oneByte byteCode;
  };

  int main()
  {
      union oneSymbol symbol;
      symbol.letter = getchar();
      // Вывод псевдобитового представления (биты заполняются справа налево) в двоичном коде:
      printf("%d", symbol.byteCode.e);
      printf("%d", symbol.byteCode.d);
      printf("%d", symbol.byteCode.c);
      printf("%d", symbol.byteCode.b);
      printf("%d", symbol.byteCode.a);
  }
 *
 * 2) Если же имеется в виду, что нам надо получить код
 *    каждой буквы, в котором она хранится в ASCII,
 *    то надо осуществлять другой вариант:
 *    В ASCII английские символы хранятся в 65-90 (большие буквы)
 *    и 97-122 (маленькие).
 *
 */

// В данном случае семь позиций, потому что
// код "z" - 01111010. Соответственно, нужны все поцизии без нуля, а можно и с нулём.
struct byte
{
    unsigned int last_7 : 1;
    unsigned int last_6 : 1;
    unsigned int last_5 : 1;
    unsigned int last_4 : 1;
    unsigned int last_3 : 1;
    unsigned int last_2 : 1;
    unsigned int last_1 : 1;
    unsigned int last_0 : 1;
};

union letter
{
    int x;
    struct byte xCode;
};

int main()
{
    // Буква для представления в битовом представлении
    char symbol;
    gets(&symbol);

    // Получение ASCII-кода этой буквы
    union letter ASCII;
    ASCII.x = symbol;

    // Печатаем, как это будет
    printf("%d", ASCII.xCode.last_0);
    printf("%d", ASCII.xCode.last_1);
    printf("%d", ASCII.xCode.last_2);
    printf("%d", ASCII.xCode.last_3);
    printf("%d", ASCII.xCode.last_4);
    printf("%d", ASCII.xCode.last_5);
    printf("%d", ASCII.xCode.last_6);
    printf("%d", ASCII.xCode.last_7);
}

// Как бы вот два варианта, я склоняюсь больше к первому, но и второй легко осуществим,
// поэтому решил записать два. Еще непонятно, куда нужно "записать" букву.



