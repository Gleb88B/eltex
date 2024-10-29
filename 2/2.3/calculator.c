#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "ariph.h"

float (*func[4])(int, ...) = {sum, diff, mult, divv};

int main(int argc, char *argv[])
{
    if (argc - 1 < 2 || argc - 1 > 5)
    {
        printf("Неверное количество аргументов\n");
    }
    int punct;
    float res;
    double args[argc-1];
        for (int i = 0; i < argc-1; i++) 
        {
            args[i] = atof(argv[i + 1]);
        }
    while (1)
    {
        punct = 0;
        res = 0;
        printf("Выберите команду:\n1. Сложение\n2. Вычитание\n3. Умножение\n4. Деление\n");
        printf("Ваши числа: \n");
        for (int i = 0; i < argc - 1; i++)
        {
            printf(" %f", args[i]);
        }
        printf("\n");
        scanf("%d", &punct);
        res = func[punct-1](argc-1, args[0], args[1], args[2], args[3], args[4]);
        printf("Результат %f\n", res);
    }
}