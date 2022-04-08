#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

#define ROW_COUNT 9
#define COLUMN_COUNT 9

int find(const int *p_array, const int size, const int key);

int main(void)
{
#ifdef __linux__
    setlocale(LC_ALL, "ru_RU.UTF-8");
#endif

#ifdef __WINNT__
    setlocale(LC_ALL, "rus"); // или setlocale(LC_ALL, "Russian");
#endif

    int matrix[ROW_COUNT][COLUMN_COUNT] = {0};
    int element = 1;
    for (int row = 0; row < ROW_COUNT; ++row)
        for (int column = 0; column < COLUMN_COUNT; ++column)
            matrix[row][column] = element++;

    int array[100] = {0};
    int indexCount = 0;
    for (int row = 0; row < ROW_COUNT; ++row) {
        for (int column = 0; column < COLUMN_COUNT; ++column) {
            int column_left = 0;
            int column_right = 0;
            if (row < ROW_COUNT / 2) {
                int column_centr = COLUMN_COUNT / 2;
                column_left = column_centr - row;
                column_right = column_centr + row;
            }
            else {
                int column_centr = COLUMN_COUNT / 2;
                column_left = row - column_centr;
                column_right = (COLUMN_COUNT - 1) - column_left;
            }
            if (column >= column_left && column <= column_right)
                array[indexCount++] = matrix[row][column];
        }
    }

    for (int row = 0; row < ROW_COUNT; ++row) {
        for (int column = 0; column < COLUMN_COUNT - 1; ++column) {
                if (find(array, indexCount, matrix[row][column]))
                    wprintf(L"\x1B[31m%d\t", matrix[row][column]);
                else
                    wprintf(L"\x1B[0m%d\t", matrix[row][column]);
        }
        if (find(array, indexCount, matrix[row][COLUMN_COUNT - 1]))
            wprintf(L"\x1B[31m%d\n", matrix[row][COLUMN_COUNT - 1]);
        else
            wprintf(L"\x1B[0m%d\n", matrix[row][COLUMN_COUNT - 1]);
    }

    int sum = 0;
    for (int index = 0; index < indexCount; ++index) {
        sum += array[index];
    }

    wprintf(L"\x1B[35mSum: %d\n", sum);
    wprintf(L"\x1B[0m\n", sum);

    return 0;
}

int find(const int *p_array, const int size, const int key)
{
    for (int index = 0; index < size; ++index)
        if (p_array[index] == key)
            return 1;
    return 0;
}
