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
 * Программа демонстрирует работу с аргументами функции main()
 *
 * Подробнее:
 * https://ru.wikipedia.org/wiki/Си_(язык_программирования)#Точка_входа_программы
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

// Аргументы argc - количество ключей, argv - сами ключи
int main(int argc, char *argv[])
{
    if (argc > 2) {
        for (size_t i = 0; i < (size_t)argc; i++)
            wprintf(L"%s ", argv[i]);
        wprintf(L" ☭\n");
    }
    else
        wprintf(L"%s\n", (wchar_t*)argv[1]);

    return 0;
}
