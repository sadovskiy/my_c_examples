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
 * Программа демонстрирует работу алгоритма шифрования гаммированием, через
 * операцию исключающие ИЛИ (XOR)
 * 
 * Подробнее:
 * https://ru.wikipedia.org/wiki/Гаммирование
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

// Латинский алфавит начинается после пробела
const wchar_t first_symbol = L' '; // 32
// Общее число доступных символов
const wchar_t number_of_characters = 2000;

void g_coding(wchar_t *input, wchar_t *gamma, wchar_t *result)
{
    size_t size_in = 0;
    size_t size_g = 0;

    while (input[size_in] != '\0') {
        size_in++;
    }

    while (gamma[size_g] != '\0') {
        size_g++;
    }

    for(size_t i = 0, j = 0; i < size_in; i++, j++)
    {
        wchar_t Ti = input[i] - first_symbol;
        wchar_t Gi = gamma[j] - first_symbol;
        wchar_t s = Ti + Gi;
        wchar_t r = first_symbol + s % number_of_characters;
        result[i] = r;
    }
}

void g_decoding(wchar_t *input, wchar_t *gamma, wchar_t *result)
{
    size_t size_in = 0;
    size_t size_g = 0;

    while (input[size_in] != '\0') {
        size_in++;
    }

    while (gamma[size_g] != '\0') {
        size_g++;
    }

    for(size_t i = 0, j = 0; i < size_in; i++, j++)
    {
        wchar_t Ci = input[i] - first_symbol;
        wchar_t Gi = gamma[j] - first_symbol;
        wchar_t s = Ci - Gi + number_of_characters;
        wchar_t r = first_symbol + s % number_of_characters;
        result[i] = r;
    }
}

int main(void)
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    wchar_t str1[100] = {0},
            gamma[100] = {0},
            rez[100] = {0};

    wprintf(L"Введите исходное сообщение: ");
    wscanf(L"%Ls", str1);
    wprintf(L"Введите гамму: ");
    wscanf(L"%Ls", gamma);

    g_coding(str1, gamma, rez);
    wprintf(L"\n");

    wprintf(L"Зашифрованное сообщение: ");
    wprintf(L"%Ls", rez);

    wprintf(L"\n");
    wprintf(L"Введите зашифрованное сообщение: ");
    wscanf(L"%Ls", rez);

    g_decoding(rez, gamma, str1);

    wprintf(L"\n");
    wprintf(L"Исходное сообщение: \n");
    wprintf(L"%Ls", str1);
    wprintf(L"\n");

    return 0;
}
