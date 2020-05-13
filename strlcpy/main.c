/*
 * Copyright (C) 2020. GPL
 *
 * Written by Sadovskiy B. S.
 *
 *
 * Права на программу (С) 2020. GPL
 *
 * Написана Садовским Б. С.
 *
 * Программа демонстрирует алгоритм безопасного копирования строки
 *
 * Подробнее:
 * https://ru.wikipedia.org/wiki/Strlcpy
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "strlfunc.h"

int main(void)
{
    char *str = "Hello world!";
    char new_str[5] = {0};

    strlcpy(new_str, str, sizeof(new_str));

    printf("%s \n", str);
    printf("%s \n", new_str);

    return 0;
}
