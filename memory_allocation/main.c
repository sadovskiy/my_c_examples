/*
 * Copyright (C) 2020. GPL
 *
 * Written by Sadovskiy B. S.
 *
 * Права на программу (С) 2020. GPL
 *
 * Написана Садовским Б. С.
 *
 * Программа демонстрирует работу с динамической памятью
 * 
 * Подробнее:
 * https://ru.wikipedia.org/wiki/Динамическое_распределение_памяти
 * https://en.wikipedia.org/wiki/Memory_management
 * https://en.wikipedia.org/wiki/C_dynamic_memory_allocation
 * https://learnc.info/c/memory_allocation.html
 * https://ru.wikipedia.org/wiki/Куча_(память)
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int main(void)
{
    // Создадим указатель неопределённого типа (не обязательно его)
    void *v_ptr = 0;

    // Выделяем память
    v_ptr = malloc(sizeof(unsigned char));

    // Проверяем была ли она выделена. Если нет, то malloc() вернёт ноль
    if (!v_ptr) {
        fprintf(stderr, "Error: Memory has not been allocated!");
        return EXIT_FAILURE;
    }

    // Присвоим значение с явным привидением типа
    *((unsigned char*)v_ptr) = 255;

    // Проверим, действительно ли переменная хранит наше значение.
    // Опять с явным приведением типа
    printf("v_ptr = %d \n", *((unsigned char*)v_ptr));

    // Если надо добавить ещё памяти можно воспользоваться функцией reallor()
    // Участок памяти будет один, а указатели должны быть разными
    unsigned char *c_ptr = realloc(v_ptr, 2 * sizeof(unsigned char));

    // Ещё раз проверим
    if (!c_ptr) {
        fprintf(stderr, "Error: Memory has not been allocated!");
        return EXIT_FAILURE;
    }

    // Присвоим новое значение
    *(c_ptr + 1) = 100;

    // Проверим новое содержимое
    printf("c_ptr[0] = %d \n", *c_ptr);
    printf("c_ptr[1] = %d \n", *(c_ptr + 1));

    // Проверим на какие адреса ссылаются указатели. Должны на один адрес.
    printf("v_ptr = %p \n", v_ptr);
    printf("c_ptr = %p \n", c_ptr);

    // Теперь освободим память, но надо понимать, что второй указатель v_ptr,
    // тоже ссылается сюда
    free(c_ptr);

    size_t size = 10;
    // Функция выделения памяти calloc() удобна для работы с массивами
    c_ptr = calloc(size, sizeof (unsigned char));

    if (!c_ptr) {
        fprintf(stderr, "Error: Memory has not been allocated!");
        return EXIT_FAILURE;
    }

    // Запишем в массив пару значений разными способами
    c_ptr[2] = 5;
    *(c_ptr + 3) = 6;

    // Посмотрим содержимое
    for (size_t i = 0; i < size; ++i) {
        printf("c_ptr[%zu] = %d\n", i, c_ptr[i]);
    }

    // Проверим на какие адреса ссылаются указатели ещё раз
    printf("v_ptr = %p \n", v_ptr);
    printf("c_ptr = %p \n", c_ptr);

    free(c_ptr);

    return 0;
}
