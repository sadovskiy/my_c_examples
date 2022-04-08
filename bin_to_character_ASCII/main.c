/*
 *
 * Copyright (C) 2022. GPL
 *
 * Written by Sadovskiy B. S.
 *
 *
 * Права на программу (С) 2022. GPL
 *
 * Написана Садовским Б. С.
 *
 * Программа расшифровывает запись в двоичном формате (в типе char).
 * Используются побитовые операции и получает строку char
 *
 *
 *
 */

#include <stdio.h>
#include <string.h>

int main()
{
    // Word: polynomial

    const char input[] = "01110000011011110110110001111001011011100110111101101101011010010110000101101100";

    unsigned char byte[20] = {0};

    for (size_t i = 0, j = 0, d = 0; i < strlen(input); i++, d++) {
        if (input[i] == '1')
            byte[j] |= 128 >> d;
        if (!(i % 8) && i >= 8)
            j++;
        if (d == 8)
            d = 0;
    }

    printf("%s\n", byte);

    return 0;
}
