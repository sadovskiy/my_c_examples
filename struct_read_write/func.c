/*
 * Copyright (C) 2020. GPL
 *
 * Written by Sadovskiy B. S.
 *
 * Права на программу (С) 2020. GPL
 *
 * Написана Садовским Б. С.
 *
 * Программа демонстрирует запись/чтение структуры
 * на языке Си
 *
 * Подробнее:
 * https://ru.wikipedia.org/wiki/Структура_(язык_Си)
 * https://ru.wikipedia.org/wiki/Strtok
 *
 *
 */

#include "func.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void write_to_file(st_student *student)
{
    FILE *out = fopen("file.txt", "w");

    if (!out) {
        fprintf(stderr, "Error: file not open!\n");
        exit(EXIT_FAILURE);
    }

    // Записываем информацию о студенте Иванове построчно в файл
    fprintf(out, "%d;%s;%s;%s;%s;%d;%d;%d;\n",
            student->id,
            student->name,
            student->surname,
            student->patronymic,
            student->facult,
            student->year,
            student->group,
            student->mark);

    fclose(out);
}

int read_to_file(st_student *student)
{
    FILE *in = fopen("file.txt", "r");

    if (!in) {
        fprintf(stderr, "Error: file not open!\n");
        exit(EXIT_FAILURE);
    }

    // Временный буфер для входных строк
    char buffer[100] = {0};
    int i = 0, j = 0;

    // Чтение посимвольно до конца файла
    while (!feof(in)) {
        char ch = fgetc(in);

        // Все символы, кроме конца строки пишем во временный буфер
        if (ch != '\n') {
            // Буфер уже закончился, а символы продолжают поступать
            if (i > 98)  {
                j++;
                continue; // Пропускаем их
            }
            else {
                buffer[i - j] = ch;
                i++;
            }
        }
        // Если попадётся конец строки, то берём буфер и
        // начинаем его разбивать на лексемы (токены).
        else {
            // Перед разбором надо убедиться, что строка была прочитана
            // правильно
            if (j) {
                fprintf(stderr, "Error: The input string is too long. "
                                "Reduce it by %d characters.\n", j);

                fclose(in);
                return READ_FAILURE;
            }

            char *pch = strtok(buffer, ";");
            student->id = atoi(pch); // Тут и далее пишем каждый токен
            pch = strtok(NULL, ";"); // в поле структуры и переходим
            strcpy(student->name, pch); // к следующей лексеме
            pch = strtok(NULL, ";");
            strcpy(student->surname, pch);
            pch = strtok(NULL, ";");
            strcpy(student->patronymic, pch);
            pch = strtok(NULL, ";");
            strcpy(student->facult, pch);
            pch = strtok(NULL, ";");
            student->year = atoi(pch);
            pch = strtok(NULL, ";");
            student->group = atoi(pch);
            pch = strtok(NULL, ";");
            student->mark = atoi(pch);

            i = 0; // Строка закончилась можно итератор обнулить
        }
    }

    printf("\n");

    fclose(in);

    return READ_SUCCESS;
}
