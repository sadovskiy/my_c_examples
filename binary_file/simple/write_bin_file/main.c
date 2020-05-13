/*
 * Copyright (C) 2020. GPL
 *
 * Written by Sadovskiy B. S.
 *
 * Права на программу (С) 2020. GPL
 *
 * Написана Садовским Б. С.
 *
 * Программа демонстрирует запись двоичного файла с целой переменной
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
//    int n = 100;
    unsigned char n = 0;

    // Ключ wb - записать файл в двоичном формате
    FILE *stream = fopen("file.bin", "wb");

    if (!stream) {
        fprintf(stderr, "Error: file not open!\n");
        exit(EXIT_FAILURE);
    }

    // Запись в файл переменной n одним блоком размеров 4 байта если int
    // или 1 байт для char
    int res = fwrite(&n, sizeof(char), 1, stream);

    if (res) printf("File was recorded.\n");
    else printf("File was not recorded.\n");

    fclose(stream);

    return 0;
}
