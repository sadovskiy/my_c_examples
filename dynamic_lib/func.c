/*
 * Copyright (C) 2020. GPL
 *
 * Written by Sadovskiy B. S.
 *
 * Права на программу (С) 2020. GPL
 *
 * Написана Садовским Б. С.
 *
 * Программа демонстрирует раздельной компиляции и создания библиотек
 *
 * Подробнее:
 * https://ru.wikipedia.org/wiki/Компилятор#Раздельная_компиляция
 *
 * Файл надо скомпилировать командой: gcc -c func.c
 *
 * Для обычной сборки не надо делать с полученным файлом func.o ничего.
 *
 * Для создания из func.o статической библиотеки надо выполнить команду:
 * ar rc libfunc.a func.o
 * ranlib libfunc.a
 *
 * Для создания из func.o динамической библиотеки надо выполнить команду:
 * gcc -fPIC -c func.c (Если у вас линукс)
 * gcc func.o -shared -o libfunc.so
 *
 * 
 */

#include <stdio.h>

#include "func.h"

void func(int n)
{
    for (register int i = 0; i < n; i++)
                fprintf(stdout, "%d\n", i);
}

void func2( void )
{
        fprintf(stdout, "Test\n");

}

void func3(const char* n)
{
        fprintf(stdout, "%s\n", n);
}
