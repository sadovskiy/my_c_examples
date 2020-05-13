/*
 * Copyright (C) 2020. GPL
 *
 * Written by Sadovskiy B. S.
 *
 * Права на программу (С) 2020. GPL
 *
 * Написана Садовским Б. С.
 *
 * Программа демонстрирует работу с указателями
 *
 * Подробнее:
 * https://ru.wikipedia.org/wiki/Указатель_(тип_данных)
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int main(void)
{
    unsigned char ch = 200;
    void *v_ptr = 0;
    unsigned char *us_ptr = 0;

    // Возьмём адрес ch и запишем его в v_ptr
    v_ptr = &ch;

    // Посмотрим, что записано в ch
    printf("ch = %d\n", ch);

//    *v_ptr = 5; // Нельзя так делать, так как указатель неопределённого типа
    // Для передачи значения указателю неопределённого типа писать только так
    *((unsigned short*)v_ptr) = 5;

    // Выведем на экран
    printf("v_ptr = %d\n", *((unsigned short*)v_ptr));

    // Сделаем явное приведение типа
    us_ptr = (void *)v_ptr;

    // Затем можно присвоить и только с гарантией, что заранее известен тип на,
    // который указывает void
    *us_ptr = 100;

    // Сделаем контрольный вывод
    printf("us_ptr = %d\n", *us_ptr);

    return 0;
}
