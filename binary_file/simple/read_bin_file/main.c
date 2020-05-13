/*
 * Copyright (C) 2020. GPL
 *
 * Written by Sadovskiy B. S.
 *
 * Права на программу (С) 2020. GPL
 *
 * Написана Садовским Б. С.
 *
 * Программа демонстрирует чтение двоичного файла с целой переменной
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    unsigned char n = 0;

    // Ключ кb - прочитать файл в двоичном формате
    FILE *stream = fopen("file.bin", "rb");

    if (!stream) {
        fprintf(stderr, "Error: file not open!\n");
        exit(EXIT_FAILURE);
    }

    // Чтение файла в переменную n одним блоком размеров 4 байта если int
    // или 1 байт для char
    int res = fread(&n, sizeof(char), 1, stream);

    if (res) printf("File was read.\n");
    else printf("File was not read.\n");

    printf("%d\n", n);

    fclose(stream);

    return 0;
}
