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
 * Программа демонстрирует работу с системой ввода/вывода широких
 * символов через конвертация символов функцией WideCharToMultiByte()
 * Для кодировки UTF-8 используется страница 65001.
 * Этот пример имеет смысл только в MS Windows
 * 
 * Подробнее:
 * https://docs.microsoft.com/en-us/windows/win32/api/stringapiset/nf-stringapiset-widechartomultibyte
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN64
#include <windows.h>
#define STR_END_CHAR_SIZE 2 // \r\n for MS Windows
#else
#define STR_END_CHAR_SIZE 1 // \n for GNU/Linux
#endif

#define BUF_SIZE 255

int main(void)
{
    // w - wide
    wchar_t wstr[BUF_SIZE] = {0};
    // mb - MultiByte (на самом деле однобайтный) и пишется в char
    // но будет занимать два соседних байта, по этому буфер надо умножить на два.
    // Код кириллической буквы 'а' будет "4 30", что требует для хранения
    // два байта. Значит в массиве на символ 'а' будут заняты mb_str[0] и
    // mb_str[1] места.
    char mb_str[BUF_SIZE * 2 + STR_END_CHAR_SIZE] = {0};

    unsigned long read;

#ifdef _WIN64
    // Извлекаем дискриптор устройства STD_INPUT_HANDLE (устройства ввода)
    // аналогична функции _fileno(stdout)
    void *console = GetStdHandle(STD_INPUT_HANDLE);

    printf("Enter the string: ");

    // Читаем ввод из console в кодеровке UTF-16. Пишем в wstr в количестве 255 символов.
    // read - это фактичестки сколько символов прочетали.
    ReadConsole(console, wstr, BUF_SIZE, &read, NULL);

    // Конвертируем прочитанные символы из широких (UTF-16) в однобайтные
    int size = WideCharToMultiByte(CP_UTF8, 0,
                                   wstr, read,
                                   mb_str,
                                   sizeof(mb_str),
                                   NULL, NULL);
#endif
    mb_str[size] = 0;

    printf("You entered: %s\n", mb_str);

    return 0;
}
