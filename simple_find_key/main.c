/*
 * Copyright (C) 2020. GPL
 *
 * Written by Sadovskiy B. S.
 *
 * Права на программу (С) 2020. GPL
 *
 * Написана Садовским Б. С.
 *
 * Программа демонстрирует поиск символа в строке
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Поиск символа key в строке str (массив символов)
int find(const char str[], const char key)
{
    size_t i = 0;
    while (str[i] != key && str[i++] != '\0');

    if (str[i - 1] == '\0')
        return 0;
    return i;
}

int main(void)
{
    int k = find("Hello World!\n", 'W');

    printf("Index sign \'W\' in string \"Hello World!\" is %d\n", k);


    return 0;
}


