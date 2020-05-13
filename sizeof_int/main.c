/*
 * Copyright (C) 2020. GPL
 *
 * Written by Sadovskiy B. S.
 *
 * Права на программу (С) 2020. GPL
 *
 * Написана Садовским Б. С.
 *
 * Программа выводит максимальные значения типов данных в Си
 *
 * Подробнее:
 * https://ru.wikipedia.org/wiki/Система_типов_Си
 *
 * 
 */

#include <stdio.h>
#include <limits.h>



int main(void)
{
    // Получаем значение констант
    int n_int = INT_MAX;
    short n_short = SHRT_MAX;
    long n_long = LONG_MAX;
    long long n_long_long = LLONG_MAX;

    // Посмотрим их размеры
    printf("int is %zu bytes.\n",  sizeof (int));
    printf("short is %zu bytes.\n", sizeof (n_short));
    printf("long is %zu bytes.\n", sizeof (n_long));
    printf("long long is %zu bytes.\n", sizeof (n_long_long));

    // Посмотрим максимальные значения
    printf("Max values: ");
    printf("int: %d\n", n_int);
    printf("short: %hd\n", n_short);
    printf("long: %ld\n", n_long);
    printf("long long: %lld\n", n_long_long);
    printf("minimum int value = %d\n", INT_MIN);
    printf("Bits per byte = %d\n", CHAR_BIT);

    return 0;
}
