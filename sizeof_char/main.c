/*
 *
 * Copyright (C) 2020. GPL
 *
 * Written by Sadovskiy B. S.
 *
 *
 * Права на программу (С) 2020. GPL
 *
 * Написана Садовским Б. С.
 *
 * Программа позволяет узнать размер в байтах типа char в Си
 * 
 * Подробнее:
 * https://ru.wikipedia.org/wiki/Система_типов_Си
 *
 * 
 */

#include <stdio.h>

int main(void)
{
    // Посмотрим размеры типов и констант в Си
    printf("size const character: %zu\n", sizeof('F'));
    printf("size char: %zu\n", sizeof(char));

    return 0;
}

