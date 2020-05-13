/*
 * Copyright (C) 2020. GPL
 *
 * Written by Sadovskiy B. S.
 *
 *
 * Права на программу (С) 2020. GPL
 *
 * Написана Садовским Б. С.
 *
 * Программа демонстрирует алгоритм безопасного копирования строки
 *
 * Подробнее:
 * https://ru.wikipedia.org/wiki/Strlcpy
 *
 *
 */

#ifndef STRLFUNC_H
#define STRLFUNC_H

#include <stdio.h>

size_t strlcpy(char *dst, const char *src, const size_t siz);

#endif // STRLFUNC_H
