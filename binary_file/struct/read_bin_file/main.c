/*
 * Copyright (C) 2020. GPL
 *
 * Written by Sadovskiy B. S.
 *
 * Права на программу (С) 2020. GPL
 *
 * Написана Садовским Б. С.
 *
 * Программа демонстрирует чтение структуры из двоичного файла
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

    FILE *stream = fopen("file.bin", "rb");

    if (!stream) {
        fprintf(stderr, "Error: file not open!\n");
        exit(EXIT_FAILURE);
    }

    int res = fread(s, sizeof(st), 1, stream);

    if (res) printf("File was read.\n");
    else printf("File was not read.\n");

    // На случай если данных не будет
    if (!(s->str))
        strcpy(s->str, "No data.\n");

    printf("%d\n", s->a);
    printf("%f\n", s->b);
    printf("%s\n", s->str);

    fclose(stream);

    free(s);
    return 0;
}
