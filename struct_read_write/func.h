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

#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

// Информация о результате чтения файла
#define READ_FAILURE 1
#define READ_SUCCESS 0

// Создаём новую структуру "Студент"
typedef struct
{
    int  id; // Идентификатор студента (например номер зачётки)
    char name[100]; // Имя студента
    char surname[100]; // Фамилия студента
    char patronymic[100]; // Отчество студента
    char facult[100]; // Институт
    int  year;          // Курс обучения
    int  group;         // Группа
    int  mark;          // Получена оценка по предмету
} st_student;

void write_to_file(st_student *student);
int read_to_file(st_student *student);

#endif // FUNC_H_INCLUDED
