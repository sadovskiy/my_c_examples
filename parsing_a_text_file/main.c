/*
 * Copyright (C) 2020. GPL
 *
 * Written by Sadovskiy B. S.
 *
 * Права на программу (С) 2020. GPL
 *
 * Написана Садовским Б. С.
 *
 * Программа демонстрирует чтение и парсинг файла
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    // Делаем несколько простых переменных, которые будем заполнять
    // прочитанными данными
    int  num = 0;
    char str[20] = {0};
    char ch = 0;
    int  n = 0;

    FILE *in = fopen("file.txt", "r");

    if (!in) {
        fprintf(stderr, "Error: file not open!\n");
        return EXIT_FAILURE;
    }

    {
        int index = 0; // Текущий символ в буферной строке
        int character = 0; // Читаемый символ
        int var = 0;    // Порядок данных заполняемых из файла
        char buffer[50] = {0}; // Строка с прочитанным набором данных
        do {
            character = fgetc(in);
            if (index >= 48) // Входная строка не должна превышать 50 символов
                // Если входящий символ не ';' то пропускаем его
                if (character != ';')
                    continue;
                else
                    buffer[index] = character; // Пришла ';' записываем её
                            // последним символом в буферной строке
            else
                buffer[index] = character;
            // Проверяем входной символ. Если это ';', то сбрасываем накопленные
            if (character == ';') { // данные
                buffer[index] = '\0'; // заменяем ';' на ноль
                // Определяем какую переменную из четырёх будем вставлять
                switch (var) {
                case 0: num = atoi(buffer); break;
                case 1: strcpy(str, buffer); break;
                case 2: ch = buffer[index - 1]; break;
                case 3: n = atoi(buffer); break;
                }
                var++; // Переменную записали,
                       // значит надо переходить к следующей
                index = 0; // Входная строка должна начаться с начала
            }
            else { // Если есть символ перехода на следующую строку
                if (character == '\n') {
                    index = 0; // Строка начинается заново
                    var = 0;   // Переменную пишем заново
                }
                else
                    index++; // Переходим к следующему символу в строке
            }
        } while (character != EOF); // Или проверять входной поток функцией feof(in);
    }

    // Выведем последнюю строчку на экран
    printf("%d \t%s \t%c \t%d \n", num, str, ch, n);

    fclose(in);

    return 0;
}
