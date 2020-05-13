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
 * Программа демонстрирует локальные и глобальные области видимости
 * 
 * Подробнее:
 * https://ru.wikipedia.org/wiki/Область_видимости
 * https://ru.wikipedia.org/wiki/Глобальная_переменная
 * https://ru.wikipedia.org/wiki/Локальная_переменная
 *
 * 
 */

#include "func.h"

#include <stdio.h>
#include <stdlib.h>

// Глобальная переменная с внутренним связыванием
static int sig = 1;
// Глобальная переменная с внешним связыванием
extern int eig;

// Глобальные переменные
int ig1 = 10, ig2 = 20;

//int eigf;

int main(void)
{
    // Локальная переменная
    int il = 99;

    // Говорим, что переменная объявлена как глобальная
    // extern чисто для наглядности
    extern int ig2;

    // Выведем глобальные переменные
    printf("static int global: %d\n", sig);
    printf("extern int global: %d\n", eig);

    printf("int global: %d\n", ig1);

    // Перекрываем глобальную переменную
    // auto чисто для наглядности
    auto int ig1 = 11;

    printf("int global: %d (overriding)\n", ig1);
    printf("int global: %d (extern)\n", ig2);

    printf("int local: %d\n", il);

    // Для проверки статической переменной вызовем два раза
    func();
    func();

    // Тут sigh не изменится так как локальна в данном файле,
    // а eigh будет со значением полученым из файла func.c
    printf("static int global header: %d\n", sigh);
    printf("extern int global header: %d\n", eigh);

    return 0;
}
