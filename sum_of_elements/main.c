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
 * Программа считает сумму элементов в указанной строке в матрице
 *
 *
 *
 *
 */

#include <stdio.h>

#define ROW_COUNT 8
#define COLUMN_COUNT 5

int sum(const int matrix[][COLUMN_COUNT], const int row);
int p_sum(const int (*p_matrix)[COLUMN_COUNT], const int row);

int main()
{
    const int matrix[][COLUMN_COUNT] = {{3, 5, 7, 3, 7},
                                        {0, 9, 2, 7, 3},
                                        {8, 6, 1, 4, 5},
                                        {4, 4, 8, 9, 0},
                                        {2, 4, 9, 3, 5},
                                        {3, 6, 9, 0, 7},
                                        {8, 2, 3, 4, 6},
                                        {9, 6, 6, 0, 0}};

    for (int row = 0; row < ROW_COUNT; ++row) {
        for (int column = 0; column < COLUMN_COUNT; ++column) {
            printf("%d ", matrix[row][column]);
        }
        printf("\n");
    }

    printf("Sum of row %d values: %d\n", 3, sum(matrix, 3));
    printf("Sum of row %d values: %d\n", 3, p_sum(matrix, 3));

    return 0;
}

int sum(const int matrix[][COLUMN_COUNT], const int row)
{
    int sum = 0;

    for (int i = 0; i < COLUMN_COUNT; ++i)
        sum += matrix[row][i];

    return sum;
}

int p_sum(const int (*p_matrix)[COLUMN_COUNT], const int row)
{
    int sum = 0;

    for (int i = 0; i < COLUMN_COUNT; ++i)
        sum += *(*(p_matrix + row) + i);

    return sum;
}
