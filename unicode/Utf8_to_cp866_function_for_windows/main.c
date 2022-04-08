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
 * В программе показан пример функции конвертации символов UTF-8 в 866
 * 
 * Подробнее:
 * https://ru.wikipedia.org/wiki/Широкий_символ
 * https://ru.wikipedia.org/wiki/Символьный_тип
 * https://ru.wikipedia.org/wiki/Printf
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Пригодно только для MS Windows
#ifdef __WINNT__ // Для компилятора MSVC лучше использовать макрос _WIN64
#include <windows.h>
#endif

void utf8_to_cp866(const wchar_t *str)
{
#ifdef __WINNT__ // Для компилятора MSVC лучше использовать макрос _WIN64
    char *buf = malloc(wcslen(str) + 1);

    // Переводим из UTF-8 в 866
    CharToOemW(str, buf);

    printf("%s", buf);

    free(buf);
#endif
}

int main(void)
{
    utf8_to_cp866(L"Привет мир!\n");

    return 0;
}
