//
// Created by sifi on 5/5/22.
//
#include <stdio.h>

void clear_stdin();

void input_array();

void output_array();

#define SIZE 10
float array[SIZE];

int main() {
    int i = SIZE - 1, j = 0, four = 4;
    float res = 0;
    float result[SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    input_array();

    __asm finit
    _new_arr:
    __asm{
            mov     cx,[i]
            push    cx

            mov     cx,[i]
            cmp     cx, 0
            jz      _end

            lea     bx, array
    };

    _cycle:
    __asm{
            fld     dword ptr[bx]

            fadd    res
            fstp    res

            add     bx, four
            loop    _cycle

            fld     dword ptr[bx]
            fadd    res

            lea     bx, result

            mov     ax,[i]
            mul[four]
            add     bx, ax

            fstp    dword ptr[bx]

            lea     bx, array

            dec[i]
            pop     cx
    };

    res = 0;
    __asm{
            loop    _new_arr
            fwait;
    };
            _end:
    __asm {
            lea     bx, array
            fld     dword ptr[bx]
            lea     bx, result
            fstp    dword ptr[bx]
    };

//    printf("%f\n", res);
//    result[SIZE - 1] = res;
    for (j = 0; j < 10; j++) {
            printf("%d) %.2f\n", j + 1, result[j]);
    }
//    output_array();
    return 0;
    }

    void input_array() {
        int scan_v;
        int i = 0;
        printf("Input 10 elements: \n");

        for (; i < SIZE; ++i) {
            do {
                scan_v = scanf("%f", &array[i]);
                while (getchar() != '\n');
                if (scan_v != 1) printf("NONONO\n");
            } while (scan_v != 1);
        }
    }

    void output_array() {
        int i = 0;
        for (; i < SIZE; i++) {
            printf("%.2f\n", array[i]);
        }
    }

    void clear_stdin() {
        char c;
        while ((c = getchar()) != '\n' && c != EOF);
    }


/*
 * Xi = Xi + Σj=0..i-1 (Xj)
 * X1 = X1 + (0)
 * X2 = X2 + (X1)
 * X3 = X3 + (X1 + X2)
 * X4 = X4 + (X1 + X2 + X3)
 */

    void c_func() {
        int i = SIZE - 1, j = 0;
        double sum = 0;
        for (; i >= 0; i--) {

            for (; j < i; j++) {
                sum += array[j];
            }

            array[i] += sum;
            sum = 0;
        }
    }
