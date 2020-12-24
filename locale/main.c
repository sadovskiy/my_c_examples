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
 * Программа позволяет установить локаль программы
 * и узнать удалось ли это сделать
 * 
 * Подробнее:
 * https://ru.wikipedia.org/wiki//Региональные_настройки_(программирование)
 * https://ru.wikipedia.org/wiki/Locale
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


int main(void)
{
    struct lconv* current_locale = 0;


    setlocale(LC_ALL, "ru_RU.UTF-8");

    // Узнаем удалось ли сменить локаль
    current_locale = localeconv();

    char* str = "Hello, world!";

    // Можно посмотреть символ валюты
    printf("%c\n", *(current_locale->currency_symbol));

    // Выведем строку
    printf("%s\n", str);

    return 0;
}
