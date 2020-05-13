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
 * Программа демонстрирует особенности ввода/вывода для однобайтных
 * и многобайтных символов
 * 
 * Подробнее:
 * https://ru.wikipedia.org/wiki/Широкий_символ
 * https://ru.wikipedia.org/wiki/Locale.h
 * https://ru.wikipedia.org/wiki/Printf
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

int main(void)
{
#ifdef __linux__
    setlocale(LC_ALL, "ru_RU.UTF-8");
#endif

#ifdef _WIN64
    setlocale(LC_ALL, "rus"); // или setlocale(LC_ALL, "Russian");
#endif

    // Пример строки набранной символами кириллицы
    wchar_t str[] = L"Пример многобайтной строки набранной кириллицей!";

    // В зависимости от того, какая функция ввода/вывода вызвана первой
    // в таком режиме и будет открыт поток.
    // Функция для отображения широких символов wprintf() откроет поток
    // в режиме вывода многобайтных символов, например, Unicod.
    // Функция для отображения однобайтных символов printf() откроет поток
    // в режиме вывода однобайтных символов, например, ASCII.

    // Варианты вывода многобайтного массива символов как строки
    wprintf(L"%S\n", str);   // %S - лучше не использовать. Не везде работает
    wprintf(L"%ls\n", str);  // %ls - стандартизирована и должна везде работать
    wprintf(L"%Ls\n", str);  // %Ls - стандартизирована и должна везде работать

    // Обычная однобайтная строка, которая теперь не показывается
    printf("These lines will not be displayed.\n");
    // Вывод многобайтной строки через однобайтную
    printf("Hello %ls!\n", L"world");

    // Так можно сбросить поток вывода
    freopen(0, "w", stdout);

    // Если не сбросить поток, то вывода ниже не будет,
    // так как поток изначально был открыт на вывод широких символов
    printf("\nOutput stream has been reset!\n");
    printf("These lines will be displayed.\n");
    printf("Hello (Привет) %ls!\n", L"world (Мир)");

    return 0;
}
