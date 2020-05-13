/*
 * Copyright (C) 2020. GPL
 *
 * Written by Sadovskiy B. S.
 *
 * Права на программу (С) 2020. GPL
 *
 * Написана Садовским Б. С.
 *
 * Программа демонстрирует запись структуры в двоичный файла
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int 	a;
    double 	b;
    char 	str[10];
} st;

int main(void)
{
    st *s = malloc(sizeof(st));

    FILE *stream = fopen("file.bin", "wb");

    if (!stream) {
        fprintf(stderr, "Error: file not open!\n");
        exit(EXIT_FAILURE);
    }

    // Заполняем нашу структуру данными
    s->a = 10;
    s->b = 23.544342;
    strcpy(s->str, "Hello");

    int res = fwrite(s, sizeof(st), 1, stream);

    if (res) printf("File was recorded.\n");
    else printf("File was not recorded.\n");

    fclose(stream);

    free(s);

    return 0;
}
