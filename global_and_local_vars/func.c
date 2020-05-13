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

// Определим глобальные переменные и инициализируем их
int eig = 5;
int eigh = 8;

void func(void)
{
    // Локальная статическая переменная без связывания
    static int sil = 5;

    // Выведем на экран и прибавим единицу
    printf("static int %d\n", sil++);

    // Выведем глобальные переменные
    printf("static int global header: %d\n", sigh++);
    printf("extern int global header: %d\n", eigh++);
}
