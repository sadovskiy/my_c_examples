/*
 * Copyright (C) 2020. GPL
 *
 * Written by Sadovskiy B. S.
 *
 * Права на программу (С) 2020. GPL
 *
 * Написана Садовским Б. С.
 *
 * Программа демонстрирует алгоритм реверса строки за один проход массива
 *
 * Подробнее:
 * https://ru.wikipedia.org/wiki/Указатель_(тип_данных)
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>

void str_reverse(char* str);

int main(void)
{
    // Строка для реверса
    char strIn[] = "Hello world!";

    str_reverse(strIn);

    printf("%s\n", strIn);

    return 0;
}

void str_reverse(char* str)
{
    // Надо заранее знать сколько элементов в массиве
    size_t len = 0;
    while (str[len] != '\0')
        len++;

    // Разворачиваем элементы за один проход
    // и без использования временной переменной
    for (size_t i = 0, j = len - 1; i <= j; i++, j--) {
        str[i] = str[i] + str[j];
        str[j] = str[i] - str[j];
        str[i] = str[i] - str[j];
    }
}
