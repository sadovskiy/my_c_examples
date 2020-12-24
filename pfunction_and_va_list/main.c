/*
 * Copyright (C) 2020. GPL
 *
 * Written by Sadovskiy B. S.
 *
 * Права на программу (С) 2020. GPL
 *
 * Написана Садовским Б. С.
 *
 * Программа демонстрирует работу с указателями на функцию
 * и функцией с переменным числом аргументов
 *
 * Подробнее:
 * https://ru.wikipedia.org/wiki/Вариативная_функция
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// Прототип функции с переменным числом аргументов
// в виде указателя на другие функции
void func(const int numf, void (*pf)(), ...);

void f1(void);
void f2(void);
void f3(void);
void f4(void);
void f5(void);
void f6(void);
void f7(void);
void f8(void);

int main(void)
{
    int f = 0;

    scanf("%d", &f);

    // Первое число указание на то какую функцию вызвать
    func(f, f1, f2 , f3, f4, f5, f6, (void (*)())0);
    // Отсчёт от нуля
    func(f, f1, f2 , f3, f4, (void (*)())0);

    printf("\n");

    return 0;
}

void func(const int numf, void (*pf)(), ...)
{
    // Для хранения указателей воспользуемся связным списком
    typedef struct M
    {
        int item; // Индекс функции
        void (*pfunction)(); // Указатель на функцию
        struct M *next; // Указатель на следующий элемент списка
    } list_menu_item;

    // Указатели на первый и последний элементы односвязного списка
    list_menu_item *first = 0;
    list_menu_item *last = 0;

    // Указатель на аргументы функции
    va_list ptr;

    int i = 0;

    // Инициализируем наш указатель
    va_start(ptr, pf);

    // Создаём первый элемент в списке
    list_menu_item *newItem = malloc(sizeof (list_menu_item));
    newItem->item = i;
    newItem->next = 0;
    newItem->pfunction = pf;
    first = last = newItem;
    i++;
    // Все последующие элементы (аргументы функции)
    while (1) {
        // Создаём временную переменную
        void (*pfunction)();

        // Берём указатель на функцию из списка аргументов и помещаем его
        pfunction = va_arg(ptr, void (*)());  // во временную переменную

        // Проверяем. Если функции закончились, то выходим
        if (!pfunction) break;

        // А если нет, то создаём ещё один элемент списка и сохраняем
        // указатель ещё на одну функцию
        list_menu_item *newItem = malloc(sizeof (list_menu_item));
        newItem->item = i;
        newItem->next = 0;
        // Сохраняем указатель на функцию в списке
        newItem->pfunction = pfunction;
        last->next = newItem;
        last = newItem;
        i++;
    }

    printf("%d ", i); // Итого было функций в списке аргументов

    // Ищем в списке номер функции которую надо вызвать
    for (list_menu_item * current = first;
         current;
         current = current->next)
        if (current->item == (numf - 1) ) {
            (*current->pfunction)(); // Вызываем эту функцию
        }

    int j = 0;
    // Чистим список
    for (list_menu_item * current = first, * next;
         current;current = next, j++) {
        next = current->next;
        free(current);
    }

    // Закрываем указатель
    va_end(ptr);
}

// Функции для динамического вызова
void f1(void)
{
    printf("f1\n");
}

void f2(void)
{
    printf("f2\n");
}

void f3(void)
{
    printf("f3\n");
}

void f4(void)
{
    printf("f4\n");
}

void f5(void)
{
    printf("f5\n");
}

void f6(void)
{
    printf("f6\n");
}

void f7(void)
{
    printf("f7\n");
}

void f8(void)
{
    printf("f8\n");
}

