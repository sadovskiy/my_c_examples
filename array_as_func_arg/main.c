/*
 * Copyright (C) 2020. GPL
 *
 * Written by Sadovskiy B. S.
 *
 * Права на программу (С) 2020. GPL
 *
 * Написана Садовским Б. С.
 *
 * Программа демонстрирует работу с передачей массивов как параметров функции
 * разными способами
 *
 * Подробнее:
 * https://ru.wikipedia.org/wiki/Указатель_(тип_данных)
 * https://ru.wikipedia.org/wiki/Функция_(программирование)
 * https://ru.wikipedia.org/wiki/Параметр_(программирование)
 * https://ru.wikipedia.org/wiki/Массив_(тип_данных)
 * https://en.wikipedia.org/wiki/Subroutine
 *
 * Двумерный массив - это одномерный массив,
 * элементами которого являются одномерные массивы.
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>

// Через указатель одномерный массив
void foo_array_1(int *ptr_to_array)
{
    printf("Through Pointer to Array");
    printf("array_1 = { ");
    for (size_t i = 0; i < 3; i++)
        printf("%d ", ptr_to_array[i]);
    printf("}\n");
}

// Через имя одномерного массива. Обязательно указывается размерность.
// Конкретный размер можно опустить
void foo_array_2(int array[])
{
    printf("Via Array Name");
    printf("array_1 = { ");
    for (size_t i = 0; i < 3; i++)
        printf("%d ", array[i]);
    printf("}\n");
}

// Через указатель двумерный массив. Обязательно указывается размерность
// внутренних одномерных массивов (количество столбцов)
void foo_array_3(int (*ptr_to_array)[5])
{
    printf("Through Pointer to Array");
    printf("\nTwo-dimensional array\n");
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 5; j++)
            printf("%d ", *(*(ptr_to_array + i) + j));
        printf("\n");
    }
}

// Или так же можно передавать с указанием размера массива в аргументах
void foo_array_4(const size_t size, int (*ptr_to_array)[size])
{
    printf("Through Pointer to Array and size in argument");
    printf("\nTwo-dimensional array\n");
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < size; j++)
            printf("%d ", *(*(ptr_to_array + i) + j));
        printf("\n");
    }
}

// Через указатель двумерный массив. Надо будет вычислять смещение при работе
// с массивом
void foo_array_5(int *ptr_to_array)
{
    printf("Through Pointer to Array");
    printf("\nTwo-dimensional array\n");
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 5; j++)
            printf("%d ", *(ptr_to_array + j + (i * 5)));
        printf("\n");
    }
}

// Через имя двумерного массива. Обязательно указывается размерность.
// Обязательно указывать размер внутренних одномерных массивов
void foo_array_6(int array[][5])
{
    printf("Via Array Name");
    printf("\nTwo-dimensional array\n");
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 5; j++)
            printf("%d ", array[i][j]);
        printf("\n");
    }
}


int main(void)
{
    int array_1[]    = { 1, 2, 3 };
    int array_2[][5] = { {11, 12, 13, 14, 15},
                         {21, 22, 23, 24, 25}
                       };

    foo_array_1(array_1);
    foo_array_2(array_1);
    printf("\n");
    foo_array_3(array_2);
    printf("\n");
    foo_array_4(5, array_2);
    printf("\n");
    foo_array_5(&array_2[0][0]);
    printf("\n");
    foo_array_6(array_2);
    printf("\n");

    return 0;
}

