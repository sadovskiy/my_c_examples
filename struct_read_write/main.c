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
 *
 *
 */

#include "func.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    // Создадим студента
    st_student ivan_ivanov;

    // Так как кто будет конкретно прочитан из файла,
    // сделаем вторую переменную с шаблонным названием
    st_student student;

    // Запишем данные по студенту Иванову
    ivan_ivanov.id = 455;
    strcpy(ivan_ivanov.name, "Ivan");
    strcpy(ivan_ivanov.surname, "Ivanov");
    strcpy(ivan_ivanov.patronymic, "Ivanovich");
    strcpy(ivan_ivanov.facult, "ISTAC");
    ivan_ivanov.year = 2;
    ivan_ivanov.group = 1;
    ivan_ivanov.mark = 5;

    // Сохраним студента в файл
    write_to_file(&ivan_ivanov);

    // А теперь прочитаем информацию о студенте из файла
    int status = read_to_file(&student);

    if (!status) {
        // Выведем на экран
        printf("id = %d\n", student.id);
        printf("Name: %s\n", student.name);
        printf("Surname: %s\n", student.surname);
        printf("Patronymic: %s\n", student.patronymic);
        printf("Facult: %s\n", student.facult);
        printf("Year: %d\n", student.year);
        printf("Group: %d\n", student.group);
        printf("Mark: %d\n", student.mark);
    }

    return 0;
}
