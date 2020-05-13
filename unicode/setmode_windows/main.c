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
 * Программа демонстрирует работу с системой ввода/вывода широких
 * символов.
 * Для кодировки UTF-8 используется страница 65001.
 * Этот пример имеет смысл только в MS Windows
 *
 * Подробнее:
 * https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/setmode?redirectedfrom=MSDN&view=vs-2019
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#ifdef _WIN64
#include <fcntl.h>
#include <io.h>
#endif

int main(void)
{
#ifdef _WIN64
    setlocale(LC_ALL, "Russian");

    wchar_t str[11] = {0};

    // _setmode - устанавливает режим перевода файла.
    // Первый аргумент это дескриптор файла, а второй режим работы с ним
    // _fileno - получает дескриптор файла, связанного с потоком (для stdout
    // обычно единица)
    // _O_U16TEXT - константа определяющая использовать UTF-16 в качестве
    // системы отображения
    // Установим режим для вывода
    _setmode(_fileno(stdout), _O_U16TEXT);

    // Контрольный вывод, должен показать "кошка 日本国". Если отображаются
    // квадраты, значит у выбранного шрифта нет этих символов. Надо поставить
    // другой шрифт
    wprintf(L"\x043a\x043e\x0448\x043a\x0430 \x65e5\x672c\x56fd\n");
    wprintf(L"Привет мир!\n");

    // Установим режим для ввода
    _setmode(_fileno(stdin), _O_U16TEXT);

    // Проверим на одном символе
    wprintf(L"Введите символ: ");

    wchar_t ch = fgetwc(stdin);
    wprintf(L"Вы ввели: \"%Lc\".\n", ch);

    wprintf(L"Теперь введите строку (не более 10 символов): ");
    wscanf(L"%Ls", str);
    wprintf(L"Вы ввели: \"%Ls\".\n", str);
#endif

    return 0;
}
