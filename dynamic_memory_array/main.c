/*
 * Copyright (C) 2020. GPL
 *
 * Written by Sadovskiy B. S.
 *
 * Права на программу (С) 2020. GPL
 *
 * Написана Садовским Б. С.
 *
 * Программа демонстрирует работу с динамическими массивами и указателями
 *
 * Подробнее:
 * https://ru.wikipedia.org/wiki/Массив_(тип_данных)
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Автоматический массив указателей (адресов памяти)
    // Можно представить как: {0x84, 0xF0, 0x35, 0xAF, 0x1B}
    // 0x84 -> 5
    // ...
    // 0x1B -> 9 // То есть на отдельные ячейки памяти где лежат данные
    int *array_ptrs[5] = {0};

    for (int i = 0; i < 5; i++) {
        // Заказываем динамическую память для каждого указателя из пяти
        array_ptrs[i] = malloc(sizeof (int));
        *array_ptrs[i] = 5 + i;  // Записываем какое-то значение в переменную
    }

    // Выведем на экран для проверки
    for (int i = 0; i < 5; i++)
        printf("%d ", *array_ptrs[i]);

    // Нельзя использовать *(array_ptrs + 1) так, как это не указатель

    printf("\n");

    // Для таких динамических переменных память надо освобождать так:
    for (int i = 0; i < 5; i++) {
        free(array_ptrs[i]);
        array_ptrs[i] = 0;
    }

    // Указатель на динамический массив
    // Можно представить как: 0x84 -> {5, 6, 7, 8, 9}
    // То есть единый блок в динамической памяти
    int *dyn_array_ptr = malloc(5 * sizeof (int));

    for (int i = 0; i < 5; i++) {
        dyn_array_ptr[i] = 5 + i;  // Записываем какое-то значение в переменную
    }

    // Выведем на экран для проверки
    for (int i = 0; i < 5; i++)
        printf("%d ", dyn_array_ptr[i]);

    printf("\n\n");

    // Освободить память просто
    free(dyn_array_ptr);
    dyn_array_ptr = 0;

    // Двумерный динамический массив
    // Выделяем память на динамический массив из 2-х указателей
    int **dyn_two_dem_array_ptr = malloc(2 * sizeof (int));

    // Выделяем динамическую память на два блока по три элемента каждый
    for (int i = 0; i < 2; i++) {
        dyn_two_dem_array_ptr[i] = malloc(3 * sizeof (int));
    }

    // Для наглядности запишем туда какие-то данные
    int n = 0;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            dyn_two_dem_array_ptr[i][j] = n++;

    // Правильнее использовать адресную арифметику
    // и писать *(*(dyn_two_dem_array_ptr + i) + j)

    // Теперь выведем их на экран
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++)
            printf("%d ", dyn_two_dem_array_ptr[i][j]);
        printf("\n");
    }

    // Память для такого массива освобождается так:
    for (int i = 0; i < 2; i++) {
        free(dyn_two_dem_array_ptr[i]);
        dyn_two_dem_array_ptr[i] = 0;
    }
    free(dyn_two_dem_array_ptr);
    dyn_two_dem_array_ptr = 0;

    return 0;
}
